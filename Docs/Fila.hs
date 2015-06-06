module Fila (Fila, crearFila, llegaPersona, longitud, iesimo, distancia)

   where

   
import Persona

data Fila = Vacia | F Persona Int Fila

   deriving Show

   
crearFila :: Fila
crearFila = Vacia

llegaPersona :: Persona -> Int -> Fila -> Fila
llegaPersona p d Vacia = F p d Vacia
llegaPersona p d1 (F persona d2 f) 
	|altura p < altura persona || (altura p == altura persona && edad p < edad persona) = F p d1 (F persona d2 f)
	|otherwise = F persona d2 (llegaPersona p d1 f)

iesima :: Fila -> Int -> Persona
iesima n (F p x f)
	|longitud (f)==n) =  p 
	|otherwise = iesimo n f
 

retirapersona:: Persona -> Fila -> Fila
retirapersona p f = sacarpersona p f (longitud f-1)

sacarpersona:: Persona -> Fila -> Int -> Fila
sacarpersona p f n |(n==-1) = crearFila
	|(iesima n f)==p = sacarpersona p f (n-1)
	|otherwise = llegaPersona (iesimo n f) distancia (n f) (sacarpersona 
