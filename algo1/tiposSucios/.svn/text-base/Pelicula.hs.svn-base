module Pelicula (Pelicula, nuevaP, nombreP, generosP, actoresP, es3DP, agruparPelisPorGeneroP, generarSagaDePeliculasP) where

import Tipos

data Pelicula = P Nombre [Genero] [Actor] Bool deriving (Show, Eq)

nuevaP :: Nombre -> [Genero] -> [Actor] -> Bool -> Pelicula
nuevaP a b c d = P a b c d

-- %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

nombreP :: Pelicula -> Nombre
nombreP (P a b c d) = a

-- %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

generosP :: Pelicula -> [Genero]
generosP (P a b c d) = b

-- %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

es3DP :: Pelicula -> Bool
es3DP (P a b c d) = d

-- %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

actoresP :: Pelicula -> [Actor]
actoresP (P a b c d) = c

-- %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

agruparPelisPorGeneroP :: [Pelicula] -> [(Genero,[Pelicula])]
agruparPelisPorGeneroP xs = sacoListaPeliculasVacias (agruparPelisPorGeneroALB xs)

sacoListaPeliculasVacias :: [(Genero,[Pelicula])] -> [(Genero,[Pelicula])]
sacoListaPeliculasVacias [x] 
	|length (snd x) > 0 = [x]
	|otherwise = []
sacoListaPeliculasVacias (x:xs) = sacoListaPeliculasVacias [x] ++ sacoListaPeliculasVacias xs

agruparPelisPorGeneroALB :: [Pelicula] -> [(Genero,[Pelicula])]
agruparPelisPorGeneroALB xs = [(Aventura,damePelisDeGenero Aventura xs),(Comedia,damePelisDeGenero Comedia xs),(Drama,damePelisDeGenero Drama xs),(Romantica,damePelisDeGenero Romantica xs),(Terror,damePelisDeGenero Terror xs)]

damePelisDeGenero :: Genero -> [Pelicula] -> [Pelicula]
damePelisDeGenero g [P a b c d]
			|elem g (generosP(P a b c d)) = [(P a b c d)]
			|otherwise = []
damePelisDeGenero g ((P a b c d):xs) = damePelisDeGenero g [(P a b c d)] ++ damePelisDeGenero g xs

-- %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

generarSagaDePeliculasP :: [Actor] -> [Genero] -> [Nombre] -> [Pelicula]
generarSagaDePeliculasP a b [] = []
generarSagaDePeliculasP a b (x:xs) = (P x b a False):(generarSagaDePeliculasP a b xs)

