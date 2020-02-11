SELECT title
FROM (SELECT movies.id, title
      FROM movies
      JOIN stars ON movies.id = stars.movie_id
      JOIN people ON stars.person_id = people.id
      WHERE name = 'Johnny Depp') AS movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE name = 'Helena Bonham Carter';