-- :load /home/andrew/Desktop/PF3/src/Persona/Persona.hs

-------------------------------

--Definicion del tipo compuesto

-------------------------------

module Persona (Persona, nacer, peso)

   where

type Nombre = String

type Edad    = Int

type Altura    = Int

type Peso    = Int

data Persona =  P Nombre Edad Altura Peso

   --deriving (Eq)

       deriving (Show,Eq)

-------------------------------
--Tipo algebraico
-------------------------------

nacer :: Nombre -> Edad -> Altura -> Peso -> Persona
nacer n e a p    = (P n e a p)

peso ::  Persona -> Peso
peso (P n e a p) = p

altura :: Persona -> Altura
altura (P _ _ a _) = a

pesoPesado :: [Persona]->Persona
pesoPesado [x]=x
pesoPesado (x:(y:xs))
	|peso(y)>peso(x)=pesoPesado(y:xs)
	|peso(y)<=peso(x)=pesoPesado(x:xs)


