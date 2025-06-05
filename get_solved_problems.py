import requests
import csv
from collections import defaultdict

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

# Function to get the problems solved by multiple users
def get_solved_problems_for_users(handles):
    all_solved_problems = defaultdict(set)  # Dictionary to store solved problems by each user
    for handle in handles:
        submissions_data = get_user_submissions(handle)
        if submissions_data and submissions_data['status'] == 'OK':
            submissions = submissions_data['result']
            solved_problems = extract_solved_problems(submissions)
            all_solved_problems[handle] = solved_problems
        else:
            print(f"No valid data for {handle}")
    return all_solved_problems

# Function to save the results into a CSV file
def save_to_csv(solved_problems, filename="problems.csv"):
    with open(filename, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(["User", "Contest ID", "Problem Index", "Problem Link"])  # Header row
        for user, problems in solved_problems.items():
            for contest_id, index in problems:
                problem_link = f"https://codeforces.com/contest/{contest_id}/problem/{index}"
                writer.writerow([user, contest_id, index, problem_link])

# List of users
users = ["username1", "username2", "username3", "username4"]

# Get solved problems for all users
solved_problems = get_solved_problems_for_users(users)

# Save the results to a CSV file
save_to_csv(solved_problems)

print("Data has been saved to 'problems.csv'.")
