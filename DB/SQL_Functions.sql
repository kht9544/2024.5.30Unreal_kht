USE BaseballData;

SELECT* FROM dbo.players;

-- FROM
-- WHERE
-- SELECT
-- ORDER BY

SELECT nameFirst, nameLast, 
DATEFROMPARTS(birthYear, birthMonth, birthDay) as 생일 ,
DATEFROMPARTS(deathYear, deathMonth, deathDay) as 사망날짜,
(deathYear - birthYear) as 생전나이
FROM players
WHERE deathYear IS NOT NULL AND DATEFROMPARTS(birthYear, birthMonth, birthDay) IS NOT NULL
ORDER BY 생전나이 DESC;

SELECT DISTINCT birthCity 
FROM players
WHERE birthCity LIKE 'New_____'; 

SELECT *
FROM players;
