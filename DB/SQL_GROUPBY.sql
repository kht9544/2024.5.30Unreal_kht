-- 집계함수
-- GROUP BY
-- HAVING

-- FROM
-- WHERE
-- GROUP BY
-- HAVING : GROUP BY 후 생긴 테이블에 한에서 조건절
-- SELECT
-- ORDER BY

-- SubQuery

SELECT *
FROM players
WHERE birthCountry IS NOT NULL
GROUP BY birthCountry

SELECT*
FROM players;

SELECT birthCountry, COUNT(lahmanID) AS playerCount
FROM players
WHERE birthCountry IS NOT NULL
GROUP BY birthCountry
HAVING COUNT(lahmanID) > 10 
ORDER BY playerCount DESC

-- batting 테이블에서 연도에 상관없이 팀별로 홈런을 친 개수대로 출력
-- 이 때 내림차순으로 정렬
SELECT *
FROM batting

SELECT teamID, SUM(HR)
FROM batting
GROUP BY teamID
ORDER BY SUM(HR) DESC

-- batting 테이블에서  최대로 많은 수의 홈런을 기록한 팀과 홈런 개수를 출력
-- 이 때 최대 홈런을 친 playerID를 출력
SELECT *
FROM batting
WHERE HR = 
(
	SELECT TOP(1) MAX(HR)
	FROM batting
	GROUP BY teamID
	ORDER BY MAX(HR) DESC
)
