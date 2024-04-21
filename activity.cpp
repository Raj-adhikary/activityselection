#include <iostream>
#include <vector>
#include <algorithm>

struct Activity {
    int start;
    int end;
};


bool compareActivities(const Activity& a1, const Activity& a2) {
    return a1.end < a2.end;
}


std::vector<Activity> selectActivities(const std::vector<Activity>& activities) {

    std::vector<Activity> sortedActivities = activities;
    std::sort(sortedActivities.begin(), sortedActivities.end(), compareActivities);


    std::vector<Activity> selectedActivities;


    selectedActivities.push_back(sortedActivities[0]);


    int lastEndTime = sortedActivities[0].end;


    for (std::size_t i = 1; i < sortedActivities.size(); ++i) {

        if (sortedActivities[i].start >= lastEndTime) {
            selectedActivities.push_back(sortedActivities[i]);
            lastEndTime = sortedActivities[i].end;
        }
    }

    return selectedActivities;
}


int main() {

    std::vector<Activity> activities = {
        {1, 3},
        {2, 5},
        {4, 7},
        {1, 8},
        {5, 9},
        {8, 10},
        {9, 11},
        {11, 14}
    };

    std::vector<Activity> selectedActivities = selectActivities(activities);


    std::cout << "Selected activities (start, end):\n";
    for (const auto& activity : selectedActivities) {
        std::cout << "(" << activity.start << ", " << activity.end << ")\n";
    }

    return 0;
}
