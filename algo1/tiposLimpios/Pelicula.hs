module Pelicula (Pelicula, nuevaP, nombreP, generosP, actoresP, es3DP, agruparPelisPorGeneroP, generarSagaDePeliculasP) where

import Tipos

data Pelicula = P Nombre [Genero] [Actor] Bool deriving (Show, Eq)
