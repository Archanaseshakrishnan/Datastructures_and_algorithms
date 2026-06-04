/*Algorithm - divide and conquer - time complexity: O(n log n) where n is the number of points*/
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <limits>
using namespace std;

using Point = pair<double, double>;

struct ClosestPair {
    double distance;
    Point p1, p2;
};

double distance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

ClosestPair brute_3_points (const vector<Point> & points) {
    double min_dist = numeric_limits<double>::max();
    ClosestPair result = {min_dist, {0, 0}, {0, 0}};
    
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            double this_dist = distance(points[i], points[j]);
            if (this_dist < min_dist) {
                min_dist = this_dist;
                result = {this_dist, points[i], points[j]};
            }
        }
    }
    return result;
}

ClosestPair smallest_dist_points_within_d (const vector<Point> & points, double min_d) {
    double min_dist = numeric_limits<double>::max();
    ClosestPair result = {min_d, {0, 0}, {0, 0}};
    
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            if (points[i].second - points[j].second > min_d) {
                continue; // Skip pairs that are too far apart in the y-coordinate
            }
            double this_dist = distance(points[i], points[j]);
            if (this_dist < min_d && this_dist < min_dist) {
                min_dist = this_dist;
                result = {this_dist, points[i], points[j]};
            }
        }
    }
    return result;
}

ClosestPair closest_points_in_a_plane_helper(const vector<Point>& points_by_x, const vector<Point>& points_by_y) {
    if (points_by_x.size() <= 3) {
        return brute_3_points(points_by_x);
    }

    size_t mid = points_by_x.size() / 2;
    Point mid_point = points_by_x[mid];

    vector<Point> left_points_by_y, right_points_by_y;
    for (const auto& point : points_by_y) {
        if (point.first < mid_point.first) {
            left_points_by_y.push_back(point);
        } else {
            right_points_by_y.push_back(point);
        }
    }

    ClosestPair left_result = closest_points_in_a_plane_helper(vector<Point>(points_by_x.begin(), points_by_x.begin() + mid), left_points_by_y);
    ClosestPair right_result = closest_points_in_a_plane_helper(vector<Point>(points_by_x.begin() + mid, points_by_x.end()), right_points_by_y);

    ClosestPair min_result = (left_result.distance < right_result.distance) ? left_result : right_result;
    double min_d = min_result.distance;

    vector<Point> strip;
    for (const auto& point : points_by_y) {
        if (abs(point.first - mid_point.first) < min_d) {
            strip.push_back(point);
        }
    }

    ClosestPair strip_result = smallest_dist_points_within_d(strip, min_d);
    
    return (strip_result.distance < min_result.distance) ? strip_result : min_result;
}

ClosestPair closest_points_in_a_plane(vector<Point> points) {
    if (points.size() < 2) return {0.0, {0, 0}, {0, 0}};

    vector<Point> points_by_y = points;
    sort(points_by_y.begin(), points_by_y.end(), [](const Point& a, const Point& b) {
        return a.second < b.second; // Sort by y-coordinate
    });
    sort(points.begin(), points.end());

    return closest_points_in_a_plane_helper(points, points_by_y);
}

// Driver code
int main() {
    vector<Point> points = {
        {2, 3}, {12, 30}, {40, 50},
        {5, 1}, {12, 10}, {3, 4}
    };

    cout << fixed << setprecision(6);
    ClosestPair result = closest_points_in_a_plane(points);
    cout << "Closest pair: (" << result.p1.first << ", " << result.p1.second << ") and ("
         << result.p2.first << ", " << result.p2.second << ")\n";
    cout << "Minimum distance = " << result.distance << "\n";

    return 0;
}
