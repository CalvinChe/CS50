SELECT title
FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
JOIN ratings ON movies.id = ratings.movie_id
Where name = "Chadwick Boseman"
ORDER BY rating DESC
LIMIT 5;