#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define fastio ios::sync_with_stdio(false); cin.tie(0);
// ----------------------------------------------------
// 1. STANDARD BINARY SEARCH - EXACT MATCH
// ----------------------------------------------------

// 1.1 Standard iterative implementation
int binarySearch(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;  // Avoid overflow
        
        if (nums[mid] == target) {
            return mid;  // Found the target
        } else if (nums[mid] < target) {
            left = mid + 1;  // Target is in the right half
        } else {
            right = mid - 1;  // Target is in the left half
        }
    }
    
    return -1;  // Target not found
}

// 1.2 Recursive implementation
int binarySearchRecursive(vector<int>& nums, int target, int left, int right) {
    if (left > right) {
        return -1;  // Base case: target not found
    }
    
    int mid = left + (right - left) / 2;
    
    if (nums[mid] == target) {
        return mid;
    } else if (nums[mid] < target) {
        return binarySearchRecursive(nums, target, mid + 1, right);
    } else {
        return binarySearchRecursive(nums, target, left, mid - 1);
    }
}

// Call the recursive function like this:
// int result = binarySearchRecursive(nums, target, 0, nums.size() - 1);

// ----------------------------------------------------
// 2. VARIATIONS FOR FINDING BOUNDS
// ----------------------------------------------------

// 2.1 Find the leftmost element equal to target (first occurrence)
int binarySearchLeftmost(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            result = mid;  // Save this result but continue searching left
            right = mid - 1;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

// 2.2 Find the rightmost element equal to target (last occurrence)
int binarySearchRightmost(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            result = mid;  // Save this result but continue searching right
            left = mid + 1;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

// 2.3 Find the first element greater than or equal to target (lower bound)
int lowerBound(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    int result = nums.size();  // Default if all elements are smaller than target
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] >= target) {
            result = mid;  // Potential answer
            right = mid - 1;  // Look for a smaller index
        } else {
            left = mid + 1;
        }
    }
    
    return result;
}

// 2.4 Find the first element greater than target (upper bound)
int upperBound(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    int result = nums.size();  // Default if all elements are smaller than or equal to target
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] > target) {
            result = mid;  // Potential answer
            right = mid - 1;  // Look for a smaller index
        } else {
            left = mid + 1;
        }
    }
    
    return result;
}

// ----------------------------------------------------
// 3. BINARY SEARCH WITH THREE-WAY COMPARISON
// ----------------------------------------------------

// 3.1 Ternary search - finds the maximum of a unimodal function
int ternarySearch(vector<int>& nums, int left, int right) {
    while (right - left > 2) {
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;
        
        if (nums[mid1] < nums[mid2]) {
            left = mid1;  // Peak is on the right side
        } else {
            right = mid2;  // Peak is on the left side or one of these points
        }
    }
    
    // Find the maximum value in the remaining range
    int maxVal = nums[left];
    int maxIdx = left;
    for (int i = left + 1; i <= right; i++) {
        if (nums[i] > maxVal) {
            maxVal = nums[i];
            maxIdx = i;
        }
    }
    
    return maxIdx;
}

// ----------------------------------------------------
// 4. ALTERNATIVE LOOP CONDITIONS
// ----------------------------------------------------

// 4.1 Using left < right condition (returns left at the end)
int binarySearchLeftBias(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;  // Note: we don't exclude mid here
        }
    }
    
    // At this point, left == right
    return (left < nums.size() && nums[left] == target) ? left : -1;
}

// 4.2 Using left < right with right-biased mid
int binarySearchRightBias(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    
    while (left < right) {
        int mid = left + (right - left + 1) / 2;  // Ceiling division
        
        if (nums[mid] > target) {
            right = mid - 1;
        } else {
            left = mid;  // Note: we don't exclude mid here
        }
    }
    
    // At this point, left == right
    return (left < nums.size() && nums[left] == target) ? left : -1;
}

// ----------------------------------------------------
// 5. BINARY SEARCH FOR ROTATED ARRAYS
// ----------------------------------------------------

// 5.1 Find target in a rotated sorted array
int searchRotatedArray(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            return mid;
        }
        
        // Check if the left half is sorted
        if (nums[left] <= nums[mid]) {
            // Check if target is in the left half
            if (nums[left] <= target && target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        // Right half is sorted
        else {
            // Check if target is in the right half
            if (nums[mid] < target && target <= nums[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    
    return -1;
}

// 5.2 Find the minimum element in a rotated sorted array
int findMinInRotatedArray(vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;
    
    // If array is not rotated
    if (nums[left] < nums[right]) {
        return left;
    }
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        // If mid element is greater than the rightmost element,
        // the minimum is in the right half
        if (nums[mid] > nums[right]) {
            left = mid + 1;
        }
        // Else, the minimum is in the left half (including mid)
        else {
            right = mid;
        }
    }
    
    return left;  // left == right at this point
}

// ----------------------------------------------------
// 6. BINARY SEARCH FOR SPECIAL PROBLEMS
// ----------------------------------------------------

// 6.1 Binary search on answer (Finding square root)
int mySqrt(int x) {
    if (x == 0) return 0;
    
    int left = 1;
    int right = x;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // Check if mid is the sqrt
        if (mid <= x / mid && (mid + 1) > x / (mid + 1)) {  // Avoid overflow
            return mid;
        } else if (mid > x / mid) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return right;  // This line should never be reached
}

// 6.2 Search in 2D sorted matrix
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) {
        return false;
    }
    
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    // Binary search treating the 2D matrix as a 1D sorted array
    int left = 0;
    int right = rows * cols - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int row = mid / cols;
        int col = mid % cols;
        
        if (matrix[row][col] == target) {
            return true;
        } else if (matrix[row][col] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return false;
}

// 6.3 Binary search for peak element (local maximum)
int findPeakElement(vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] > nums[mid + 1]) {
            // Peak is in the left half (including mid)
            right = mid;
        } else {
            // Peak is in the right half
            left = mid + 1;
        }
    }
    
    // At this point, left == right
    return left;
}

// 6.4 Find kth smallest element in two sorted arrays
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    // Ensure nums1 is the smaller array for simplicity
    if (nums1.size() > nums2.size()) {
        return findMedianSortedArrays(nums2, nums1);
    }
    
    int x = nums1.size();
    int y = nums2.size();
    int low = 0;
    int high = x;
    
    while (low <= high) {
        int partitionX = (low + high) / 2;
        int partitionY = (x + y + 1) / 2 - partitionX;
        
        // If partitionX is 0, use INT_MIN for maxX
        // If partitionX is x, use INT_MAX for minX
        int maxX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
        int minX = (partitionX == x) ? INT_MAX : nums1[partitionX];
        
        int maxY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
        int minY = (partitionY == y) ? INT_MAX : nums2[partitionY];
        
        if (maxX <= minY && maxY <= minX) {
            // We found the correct partition
            
            // If total length is odd
            if ((x + y) % 2 != 0) {
                return max(maxX, maxY);
            }
            
            // If total length is even
            return (max(maxX, maxY) + min(minX, minY)) / 2.0;
        } else if (maxX > minY) {
            // Move left in X
            high = partitionX - 1;
        } else {
            // Move right in X
            low = partitionX + 1;
        }
    }
    
    // If we reach here, the arrays are not sorted
    return -1;
}