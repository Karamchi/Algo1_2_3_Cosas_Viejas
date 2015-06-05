module Ticket (Ticket, nuevoT, salaT, peliculaT, usadoT, usarT, peliculaMenosVistaT, todosLosTicketsParaLaMismaSalaT, cambiarSalaT) 	where

import Tipos
import Pelicula

data Ticket = TicketSinUsar Sala Pelicula | TicketUsado Ticket deriving (Show, Eq)

nuevoT :: Pelicula -> Sala -> Bool -> Ticket
nuevoT x y u
	|u == True = TicketUsado (TicketSinUsar y x)
	|otherwise = TicketSinUsar y x
peliculaT :: Ticket -> Pelicula
peliculaT (TicketSinUsar x y) = y
peliculaT (TicketUsado x) = peliculaT x

salaT :: Ticket -> Sala
salaT (TicketSinUsar x y) = x
salaT (TicketUsado x) = salaT x

usadoT :: Ticket -> Bool
usadoT (TicketSinUsar _ _ )= False
usadoT (TicketUsado _ ) = True

usarT :: Ticket -> Ticket
usarT x = TicketUsado x

peliculaMenosVistaT :: [Ticket] -> Pelicula
peliculaMenosVistaT [x] = peliculaT x
peliculaMenosVistaT xs = elemMenosVisto (pelisDeTickets xs) xs

pelisDeTickets ::  [Ticket] -> [Pelicula]
pelisDeTickets [] = []
pelisDeTickets (x:xs) = (peliculaT x):pelisDeTickets (xs)

elemMenosVisto :: [Pelicula] -> [Ticket] -> Pelicula
elemMenosVisto [x] t = x
elemMenosVisto (x:(y:xs)) t
	|aparicionEnT x t<= aparicionEnT y t = elemMenosVisto (x: xs) t
	|otherwise = elemMenosVisto (y: xs) t
	
aparicionEnT ::  Pelicula -> [Ticket] -> Int
aparicionEnT n [] = 0
aparicionEnT n (x:xs)
	|usadoT x && n == peliculaT x = 1 + (aparicionEnT n xs)
	|otherwise = (aparicionEnT n xs)

todosLosTicketsParaLaMismaSalaT :: [Ticket] -> Bool
todosLosTicketsParaLaMismaSalaT [] = True
todosLosTicketsParaLaMismaSalaT [x] = True
todosLosTicketsParaLaMismaSalaT (x:y:xs) 
	|salaT x == salaT y = todosLosTicketsParaLaMismaSalaT (y:xs)
	|otherwise = False

cambiarSalaT :: [Ticket] -> Sala -> Sala -> [Ticket]
cambiarSalaT [] a b = []
cambiarSalaT (x:xs) a b 
	|salaT x == a && ((usadoT x) ==True )= (TicketUsado (TicketSinUsar b (peliculaT x))):cambiarSalaT xs a b
	|salaT x == a && ((usadoT x) ==False)= (TicketSinUsar b (peliculaT x)):cambiarSalaT xs a b
	|otherwise = x:cambiarSalaT xs a b
