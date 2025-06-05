import requests
import time
from datetime import datetime
import json
from collections import Counter
import csv
from typing import List, Dict

# Constants
RANKS = {"master", "international master", "grandmaster", "international grandmaster", "legendary grandmaster"}
API_BASE = "https://codeforces.com/api"
RATE_LIMIT_DELAY = 1.5  # seconds

# Step 1: Get all rated users
def get_all_rated_users():
    url = f"{API_BASE}/user.ratedList?activeOnly=false"
    response = requests.get(url)
    response.raise_for_status()
    users = response.json()["result"]
    # Filter users with rank Master and above
    master_users = [u["handle"] for u in users if u.get("rank", "").lower() in RANKS]
    return master_users

# Step 2: Get rating history of a user
def get_rating_history(handle):
    url = f"{API_BASE}/user.rating?handle={handle}"
    response = requests.get(url)
    if response.status_code != 200:
        return []
    return response.json()["result"]

# Step 3: Check if a user went from <600 to >=2100 in 12 to 15 months
def is_valid_progression(rating_changes):
    low_index = high_index = None
    for i, change in enumerate(rating_changes):
        if low_index is None and change["newRating"] < 600:
            low_index = i
        if low_index is not None and change["newRating"] >= 2100:
            high_index = i
            break
    if low_index is not None and high_index is not None:
        t1 = datetime.fromtimestamp(rating_changes[low_index]["ratingUpdateTimeSeconds"])
        t2 = datetime.fromtimestamp(rating_changes[high_index]["ratingUpdateTimeSeconds"])
        months_diff = (t2.year - t1.year) * 12 + (t2.month - t1.month)
        return 12 <= months_diff <= 15
    return False

# Main function to filter users
def find_qualified_users(limit=1000):
    qualified = []
    all_users = get_all_rated_users()
    time.sleep(RATE_LIMIT_DELAY)
    for handle in all_users:
        time.sleep(RATE_LIMIT_DELAY)
        ratings = get_rating_history(handle)
        if is_valid_progression(ratings):
            qualified.append(handle)
        if len(qualified) >= limit:
            break
    return qualified

# Function to get submissions for a user
def get_user_submissions(handle):
    url = f"https://codeforces.com/api/user.status?handle={handle}"
    response = requests.get(url)
    if response.status_code == 200:
        return response.json()  # Returns a JSON object
    else:
        print(f"Failed to retrieve submissions for {handle}")
        return None

# Function to extract solved problems from the submissions
def extract_solved_problems(submissions):
    solved_problems = set()  # Use a set to avoid duplicates
    for submission in submissions:
        if submission['verdict'] == 'OK':  # 'OK' means the problem was solved
            problem = submission['problem']
            solved_problems.add((problem['contestId'], problem['index']))  # Store contestId and index
    return solved_problems

def get_solved_problems_by_user(handle):
        submissions_data = get_user_submissions(handle)
        if submissions_data and submissions_data['status'] == 'OK':
            submissions = submissions_data['result']
            solved_problems = extract_solved_problems(submissions)
            return solved_problems
        else:
            print(f"No valid data for {handle}")


qualified_users = find_qualified_users()
qualified_users[:10]  # Show sample output


# Collect all problems solved by qualified users
problem_counter = Counter()
user_problem_map: Dict[str, List[str]] = {}

for user in qualified_users:
    time.sleep(RATE_LIMIT_DELAY)
    problems = get_solved_problems_by_user(user)
    user_problem_map[user] = problems
    problem_counter.update(problems)

# Get the top 150 most frequently solved problems
top_problems = problem_counter.most_common(150)

# Output to CSV
csv_filename = "/mnt/data/top_150_problems.csv"
with open(csv_filename, mode="w", newline="") as file:
    writer = csv.writer(file)
    writer.writerow(["Problem ID", "Times Solved", "Problem URL"])
    for problem_id, count in top_problems:
        contest_id, index = problem_id.split("-")
        url = f"https://codeforces.com/problemset/problem/{contest_id}/{index}"
        writer.writerow([problem_id, count, url])

csv_filename  # Return the file path for download or verification
