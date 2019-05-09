// Problem: 10901 - Ferry Loading III
// Link: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1842
// Solution: Mai Thanh Hiep

#include <iostream>
#include <queue>
#include <vector>
#include <climits>
using namespace std;

#define LEFT_BANK 0
#define RIGHT_BANK 1

struct Car {
    int id;
    int arrivalTime;

    Car(int _id, int _arrivalTime) : id(_id), arrivalTime(_arrivalTime) {};
};

int main() {
    int n, t, m;
    int c;
    int arrivalTime;
    char bank[10];
    scanf("%d", &c);

    while (c--) {
        scanf("%d %d %d", &n, &t, &m);

        queue<Car> cars[2];
        vector<int> uploadedTime(m);
        for (int i = 0; i < m; i++) {
            scanf("%d %s", &arrivalTime, bank);

            if (bank[0] == 'l') { // left
                cars[LEFT_BANK].push(Car(i, arrivalTime));
            } else {
                cars[RIGHT_BANK].push(Car(i, arrivalTime));
            }
        }

        int currentTime = 0;
        int currentBank = LEFT_BANK;
        while (!cars[LEFT_BANK].empty() || !cars[RIGHT_BANK].empty()) {
            // "If there are no cars waiting on either bank,
            // the ferry waits until one arrives,.."
            int earliestCar = INT_MAX;
            if (!cars[LEFT_BANK].empty())
                earliestCar = cars[LEFT_BANK].front().arrivalTime;
            if (!cars[RIGHT_BANK].empty())
                earliestCar = min(earliestCar, cars[RIGHT_BANK].front().arrivalTime);

            currentTime = max(currentTime, earliestCar);

            int carCount = 0;
            // load max n possible cars in currentBank
            while (!cars[currentBank].empty()
                   && carCount < n
                   && cars[currentBank].front().arrivalTime <= currentTime) {
                uploadedTime[cars[currentBank].front().id] = currentTime + t;
                cars[currentBank].pop();
                ++carCount;
            }

            // move to opposite bank
            currentTime += t;
            currentBank = 1 - currentBank;
        }

        for (int i = 0; i < m; ++i)
            printf("%d\n", uploadedTime[i]);

        if (c)
            printf("\n");
    }

    return 0;
}
