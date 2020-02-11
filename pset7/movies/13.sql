SELECT DISTINCT name
FROM (SELECT movie_id
      FROM stars
      JOIN people ON stars.person_id = people.id
      WHERE name = 'Kevin Bacon' AND birth = '1958') AS movies
JOIN stars ON movies.movie_id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE NOT id = (SELECT id FROM people WHERE name = 'Kevin Bacon' AND birth = '1958');