module Cine (nuevoC, nombreC, peliculasC, salasC, espectadoresC, salaC, ticketsVendidosC,  abrirSalaC, agregarPeliculaC, cerrarSalaC, cerrarSalasC, cerrarSalasDeLaCadenaC, peliculaC, venderTicketC, ingresarASalaC, pasarA3DUnaPeliculaC ) where

import Tipos
import Pelicula
import Ticket

data Cine = C Nombre | 
			SalaSinPelicula Cine Sala | 
			SalaConPelicula Cine Sala Pelicula Int | 
			TicketVendido Cine Ticket deriving (Show)

nuevoC :: Nombre -> Cine
nuevoC x = C x 

nombreC :: Cine -> Nombre
nombreC (C x) = x
nombreC (SalaSinPelicula x y) = nombreC x
nombreC (SalaConPelicula x y z a) = nombreC x
nombreC (TicketVendido x y) = nombreC x


peliculasC :: Cine -> [Pelicula]
peliculasC (C x) = []
peliculasC (SalaSinPelicula x y) = peliculasC x
peliculasC (SalaConPelicula x y z a) = z:peliculasC x
peliculasC (TicketVendido x y) = peliculasC x

salasC :: Cine -> [Sala]
salasC (C x) = []
salasC (SalaSinPelicula x y) = y:(salasC x)
salasC (SalaConPelicula x y z a) = y:(salasC x)
salasC (TicketVendido x y) = salasC x

espectadoresC :: Cine -> Sala -> Int
espectadoresC (SalaSinPelicula x y) z
	|z==y = 0
	|otherwise = espectadoresC x z
espectadoresC (TicketVendido x y) z = espectadoresC x z
espectadoresC (SalaConPelicula x y a b) z
	|z==y = b
	|otherwise = espectadoresC x z

salaC :: Cine -> Pelicula -> Sala 
salaC (SalaSinPelicula x y) p = salaC x p
salaC (TicketVendido x y) p = salaC x p 
salaC (SalaConPelicula x y z a) p 
	| z == p = y
	| otherwise  = salaC x p


ticketsVendidosC :: Cine -> [Ticket]
ticketsVendidosC (C x) = []
ticketsVendidosC (SalaSinPelicula x y) = ticketsVendidosC x 
ticketsVendidosC (SalaConPelicula x y z a) = ticketsVendidosC x 
ticketsVendidosC (TicketVendido x y)
	|usadoT y == False = y:(ticketsVendidosC x)
	|otherwise = (ticketsVendidosC x)

peliculaC :: Cine -> Sala -> Pelicula 
peliculaC (SalaSinPelicula x y) p = peliculaC x p 
peliculaC (TicketVendido x y) p = peliculaC x p
peliculaC (SalaConPelicula x y z a) p 
	|y==p = z
	|otherwise = peliculaC x p


venderTicketC :: Cine -> Pelicula -> (Cine , Ticket)
venderTicketC x y = (TicketVendido x (nuevoT y (salaC x y) False), nuevoT y (salaC x y) False)


abrirSalaC :: Cine -> Sala -> Cine
abrirSalaC x y = SalaSinPelicula x y

agregarPeliculaC :: Cine -> Pelicula -> Sala ->  Cine
agregarPeliculaC x y z = (SalaConPelicula (cerrarSalaC x z) z y 0)

cerrarSalaC :: Cine -> Sala -> Cine
cerrarSalaC (C x) s = C x 
cerrarSalaC (TicketVendido x y) s = TicketVendido (cerrarSalaC x s) y
cerrarSalaC (SalaSinPelicula x y) s
	|y == s = x
	|otherwise = SalaSinPelicula (cerrarSalaC x s) y
cerrarSalaC (SalaConPelicula x y z b) s
	|y == s = x
	|otherwise = SalaConPelicula (cerrarSalaC x s) y z b

cerrarSalasC :: Cine -> Int -> Cine
cerrarSalasC (C x) n = C x 
cerrarSalasC (TicketVendido x y) n = TicketVendido (cerrarSalasC x n) y
cerrarSalasC (SalaSinPelicula x y) n = cerrarSalasC x n
cerrarSalasC (SalaConPelicula x y z b) n
	|b < n = cerrarSalasC x n
	|otherwise = (SalaConPelicula (cerrarSalasC x n)) y z b

cerrarSalasDeLaCadenaC :: [Cine] -> Int -> [Cine]
cerrarSalasDeLaCadenaC [x] e = [cerrarSalasC x e]
cerrarSalasDeLaCadenaC (x:xs) e = ((cerrarSalasC x e):(cerrarSalasDeLaCadenaC xs e))

ingresarASalaC :: Cine -> Sala -> Ticket -> (Cine,Ticket)
ingresarASalaC x s t = (modificaC x s t,ticketCinePelicula t)

ticketCinePelicula :: Ticket -> Ticket
ticketCinePelicula t = (usarT(t))

modificaC :: Cine -> Sala -> Ticket -> Cine
modificaC (TicketVendido x y) s t 
	|y == t = (modificaC x s t)
	|otherwise = TicketVendido (modificaC x s t) y
modificaC (SalaSinPelicula x y) s t = SalaSinPelicula (modificaC x s t) y
modificaC (SalaConPelicula x y z b) s t
	|y == s = SalaConPelicula x y z (b+1)
	|otherwise = SalaConPelicula (modificaC x s t) y z b

pasarA3DUnaPeliculaC :: Cine -> Nombre -> (Cine,Pelicula)
pasarA3DUnaPeliculaC x  p = ((pasarA3DUnaPeliculaC2 x (buscoPelis (peliculasC x) p)),(nuevaP p (generosP (buscoPelis (peliculasC x) p)) (actoresP (buscoPelis (peliculasC x) p)) True))

pasarA3DUnaPeliculaC2 :: Cine -> Pelicula -> Cine
pasarA3DUnaPeliculaC2 (TicketVendido x y) p
	|peliculaT y == p = TicketVendido (pasarA3DUnaPeliculaC2 x p) (nuevoT (nuevaP (nombreP p) (generosP p) (actoresP p) True) (salaT y) False)
	|otherwise = TicketVendido (pasarA3DUnaPeliculaC2 x p) y
pasarA3DUnaPeliculaC2 (SalaSinPelicula x y) p = (SalaSinPelicula (pasarA3DUnaPeliculaC2 x p) y)
pasarA3DUnaPeliculaC2 (SalaConPelicula x y z b) p
	| p == z = (SalaConPelicula x y (nuevaP (nombreP p) (generosP p) (actoresP p) True) b)
	|otherwise = (SalaConPelicula (pasarA3DUnaPeliculaC2 x p) y z b)
 

buscoPelis :: [Pelicula] -> Nombre -> Pelicula
buscoPelis [x] n
	|nombreP x==n = x
	|otherwise = error"no existe esa pelicula"
buscoPelis (x:xs) n
	|nombreP x==n = x
	|otherwise = buscoPelis (xs) n
