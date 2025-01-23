-- FROM
-- WHERE
-- SELECT
-- ORDER BY

-- * : All
-- ASC : 오름차순 ASCENDING의 약자
-- DESC : 내림차순 DESCENGING의 약자
SELECT *
FROM dbo.Customers;

SELECT *
FROM dbo.Customers
WHERE FirstName = 'Adam' AND MiddleInitial IS NULL;

SELECT TOP(100) FirstName
FROM dbo.Customers;

SELECT *
FROM dbo.Products
ORDER BY Price DESC;
