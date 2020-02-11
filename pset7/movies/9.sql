SELECT name
FROM people
WHERE id IN (SELECT DISTINCT people.id
             FROM people
             JOIN stars ON people.id = stars.person_id
             JOIN movies ON stars.movie_id = movies.id
             WHERE year = 2004)
ORDER BY birth;