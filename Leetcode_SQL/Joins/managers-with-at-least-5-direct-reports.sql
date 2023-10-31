# https://leetcode.com/problems/managers-with-at-least-5-direct-reports/

# 1. Inner join to get the corresponding manager name for each of the employees
# 2. Then group by managerId
# 3. Finally project the name of the manager with reportees >= 5
SELECT name
FROM (
    SELECT name, count(managerId) AS reportees
    FROM (
        SELECT e1.managerId, e2.name
        FROM Employee as e1
        JOIN Employee as e2 ON e1.managerId = e2.id
    ) emp
    GROUP BY managerId
) e
WHERE reportees >= 5;
