module Main where

import HUnit
import Pelicula
import Tipos
import Ticket
import Cine


-- Auxiliares

count::Eq a => a -> [a] -> Int
count _ [] = 1
count e (l:ls) = (if (e==l) then 1 else 0) + (count e ls)

mismosAux::Eq a => [a] -> [a] -> [a] -> Bool
mismosAux x y [] = True
mismosAux x y (l:ls) = ((count l x) == (count l y)) && (mismosAux x y ls)

mismos::Eq a => [a] -> [a] -> Bool
mismos x y = mismosAux x y (x++y)

sacarRepetidos :: Eq a => [a] -> [a]
sacarRepetidos [] = []
sacarRepetidos (x:xs)   | x `elem` xs = sacarRepetidos xs
                        | otherwise = x : sacarRepetidos xs

primeros :: [(a, b)] -> [a]
primeros [] = []
primeros ((x, _):xs) = x:(primeros xs)

segundos :: [(a, b)] -> [b]
segundos = map snd


-- Auxiliares para los aseguras.
cuenta :: Eq a => [a] -> a -> Int
cuenta xs x = length $ filter (==x) xs

sinRepetidos :: Eq a => [a] -> Bool
sinRepetidos xs = all (\x -> cuenta xs x == 1) xs

sinCopiasEnGrupos :: [(Genero, [Pelicula])] -> Bool
sinCopiasEnGrupos = all (\xs -> sinRepetidos (snd xs))



-- Pelicula

p1 = nuevaP "Son Todos Iguales" [Comedia, Romantica] ["Lito Cruz", "Rodrigo de la Serna", "Soledad Villamil"] False
p2 = nuevaP "Sanata para Piano" [Comedia, Drama] ["Diego Peretti", "Roberto Carnaghi"] False
p3 = nuevaP "Dalai Lima" [Drama] ["Guillermo Francella"] True
p4 = nuevaP "Trompada de Falopio" [Aventura, Comedia, Terror] ["Mirtha Legrand", "China Zorrilla"] False

testNombrePelicula1 = TestCase (
		assertEqual 
		"El observador nombre no devuelve el valor esperado" "Son Todos Iguales"
		(nombreP p1)
	)

testNombrePelicula2 = TestCase (
		assertEqual 
		"El observador nombre no devuelve el valor esperado" "Sanata para Piano"
		(nombreP p2)
	)

testNombrePelicula3 = TestCase (
		assertEqual 
		"El observador nombre no devuelve el valor esperado" "Dalai Lima" 
		(nombreP p3)
	)

testNombrePelicula4 = TestCase (
		assertEqual 
		"El observador nombre no devuelve el valor esperado" "Trompada de Falopio"
		(nombreP p4)
	)

testGenerosPelicula1 = TestCase (
		assertEqual 
		"El observador generos no devuelve el valor esperado" 
		[Comedia, Romantica] (generosP p1)
	)

testGenerosPelicula2 = TestCase (
		assertEqual 
		"El observador generos no devuelve el valor esperado" 
		[Comedia, Drama] (generosP p2)
	)

testGenerosPelicula3 = TestCase (
		assertEqual 
		"El observador generos no devuelve el valor esperado" 
		[Drama] (generosP p3)
	)

testGenerosPelicula4 = TestCase (
		assertEqual 
		"El observador generos no devuelve el valor esperado" 
		[Aventura, Comedia, Terror] (generosP p4)
	)

testActoresPelicula1 = TestCase (
		assertBool 
		"El observador actores no devuelve el valor esperado" 
		(mismos ["Lito Cruz", "Rodrigo de la Serna", "Soledad Villamil"] (actoresP p1))
	)

testActoresPelicula2 = TestCase (
		assertBool 
		"El observador actores no devuelve el valor esperado" 
		(mismos ["Diego Peretti", "Roberto Carnaghi"] (actoresP p2))
	)

testActoresPelicula3 = TestCase (
		assertBool 
		"El observador actores no devuelve el valor esperado" 
		(mismos ["Guillermo Francella"] (actoresP p3))
	)

testActoresPelicula4 = TestCase (
		assertBool 
		"El observador actores no devuelve el valor esperado" 
		(mismos ["Mirtha Legrand", "China Zorrilla"] (actoresP p4))
	)

testEs3DPelicula1 = TestCase (
		assertEqual 
		"El observador es3D no devuelve el valor esperado" 
		False (es3DP p1)
	)

testEs3DPelicula2 = TestCase (
		assertEqual 
		"El observador es3D no devuelve el valor esperado" 
		False (es3DP p2)
	)

testEs3DPelicula3 = TestCase (
		assertEqual 
		"El observador es3D no devuelve el valor esperado" 
		True (es3DP p3)
	)

testEs3DPelicula4 = TestCase (
		assertEqual 
		"El observador es3D no devuelve el valor esperado" 
		False (es3DP p4)
	)

testAgruparPelisPorGeneroNoHayGenerosRepetidos1 = TestCase (
		assertBool 
		"Hay generos repetidos al agrupar peliculas por genero"  
		(mismos (sacarRepetidos (primeros (agruparPelisPorGeneroP [p1]))) (primeros (agruparPelisPorGeneroP [p1])))
	)

testAgruparPelisPorGeneroNoHayGenerosRepetidos2 = TestCase (
		assertBool 
		"Hay generos repetidos al agrupar peliculas por genero"  
		(mismos (sacarRepetidos (primeros (agruparPelisPorGeneroP [p2]))) (primeros (agruparPelisPorGeneroP [p2])))
	)

testAgruparPelisPorGeneroNoHayGenerosRepetidos3 = TestCase (
		assertBool 
		"Hay generos repetidos al agrupar peliculas por genero"  
		(mismos (sacarRepetidos (primeros (agruparPelisPorGeneroP [p3]))) (primeros (agruparPelisPorGeneroP [p3])))
	)

testAgruparPelisPorGeneroNoHayGenerosRepetidos4 = TestCase (
		assertBool 
		"Hay generos repetidos al agrupar peliculas por genero"  
		(mismos (sacarRepetidos (primeros (agruparPelisPorGeneroP [p4]))) (primeros (agruparPelisPorGeneroP [p4])))
	)

testAgruparPelisPorGeneroNoHayGenerosRepetidos5 = TestCase (
		assertBool 
		"Hay generos repetidos al agrupar peliculas por genero"  
		(mismos (sacarRepetidos (primeros (agruparPelisPorGeneroP [p1,p2]))) (primeros (agruparPelisPorGeneroP [p1,p2])))
	)

testAgruparPelisPorGeneroNoHayGenerosRepetidos6 = TestCase (
		assertBool 
		"Hay generos repetidos al agrupar peliculas por genero"  
		(mismos (sacarRepetidos (primeros (agruparPelisPorGeneroP [p2,p4]))) (primeros (agruparPelisPorGeneroP [p2,p4])))
	)

testAgruparPelisPorGeneroNoHayGenerosRepetidos7 = TestCase (
		assertBool 
		"Hay generos repetidos al agrupar peliculas por genero"  
		(mismos (sacarRepetidos (primeros (agruparPelisPorGeneroP [p1,p3,p4]))) (primeros (agruparPelisPorGeneroP [p1,p2,p4])))
	)

testAgruparPelisPorGeneroNoHayGenerosRepetidos8 = TestCase (
		assertBool 
		"Hay generos repetidos al agrupar peliculas por genero"  
		(mismos (sacarRepetidos (primeros (agruparPelisPorGeneroP [p1,p2,p3,p4]))) (primeros (agruparPelisPorGeneroP [p1,p2,p3,p4])))
	)

testAgruparPelisPorGeneroSinCopiasEnGrupos1 = TestCase (
		assertBool 
		"Hay peliculas repetidas al agrupar peliculas por genero" 
        (sinCopiasEnGrupos (agruparPelisPorGeneroP [p1]))
	)

testAgruparPelisPorGeneroSinCopiasEnGrupos2 = TestCase (
		assertBool 
		"Hay peliculas repetidas al agrupar peliculas por genero" 
		(sinCopiasEnGrupos (agruparPelisPorGeneroP [p2]))
	)

testAgruparPelisPorGeneroSinCopiasEnGrupos3 = TestCase (
		assertBool 
		"Hay peliculas repetidas al agrupar peliculas por genero" 
		(sinCopiasEnGrupos (agruparPelisPorGeneroP [p3]))
	)

testAgruparPelisPorGeneroSinCopiasEnGrupos4 = TestCase (
		assertBool 
		"Hay peliculas repetidas al agrupar peliculas por genero" 
		(sinCopiasEnGrupos (agruparPelisPorGeneroP [p4]))
	)

testAgruparPelisPorGeneroSinCopiasEnGrupos5 = TestCase (
		assertBool 
		"Hay peliculas repetidas al agrupar peliculas por genero" 
        (sinCopiasEnGrupos (agruparPelisPorGeneroP [p1, p2]))
	)

testAgruparPelisPorGeneroSinCopiasEnGrupos6 = TestCase (
		assertBool 
		"Hay peliculas repetidas al agrupar peliculas por genero"
        (sinCopiasEnGrupos (agruparPelisPorGeneroP [p2, p4])) 
	)

testAgruparPelisPorGeneroSinCopiasEnGrupos7 = TestCase (
		assertBool 
		"Hay peliculas repetidas al agrupar peliculas por genero" 
        (sinCopiasEnGrupos (agruparPelisPorGeneroP [p1, p3, p4])) 
	)

testAgruparPelisPorGeneroSinCopiasEnGrupos8 = TestCase (
		assertBool 
		"Hay peliculas repetidas al agrupar peliculas por genero" 
        (sinCopiasEnGrupos (agruparPelisPorGeneroP [p1, p2, p3, p4])) 
	)

testAgruparPelisPorGeneroEstanTodasYNoHayDeMas1 = TestCase (
		assertEqual 
		"El resultado no es el esperado al agrupar peliculas por genero" 
		[(Drama,[p3])] (agruparPelisPorGeneroP [p3])
	)

testAgruparPelisPorGeneroEstanTodasYNoHayDeMas2 = TestCase (
		assertBool 
		"El resultado no es el esperado al agrupar peliculas por genero" 
		(elem (Comedia,[p1]) (agruparPelisPorGeneroP [p1]))
	)

testAgruparPelisPorGeneroEstanTodasYNoHayDeMas3 = TestCase (
		assertBool 
		"El resultado no es el esperado al agrupar peliculas por genero" 
		(elem (Romantica,[p1]) (agruparPelisPorGeneroP [p1]))
	)

testAgruparPelisPorGeneroEstanTodasYNoHayDeMas4 = TestCase (
		assertBool 
		"El resultado no es el esperado al agrupar peliculas por genero" 
		(elem (Drama,[p2]) (agruparPelisPorGeneroP [p1,p2]))
	)

testAgruparPelisPorGeneroEstanTodasYNoHayDeMas5 = TestCase (
		assertBool 
		"El resultado no es el esperado al agrupar peliculas por genero" 
		(elem (Romantica,[p1]) (agruparPelisPorGeneroP [p1,p2]))
	)

testAgruparPelisPorGeneroEstanTodasYNoHayDeMas6 = TestCase (
		assertBool 
		"El resultado no es el esperado al agrupar peliculas por genero" 
		(3 == (length (agruparPelisPorGeneroP [p1,p2])))
	)

testGenerarSagaDePeliculasTieneLongitudCorrecta1 = TestCase (
		assertBool 
		"La longitud no es correcta al generar una saga de peliculas" 
		(2 == (length (generarSagaDePeliculasP ["Javier","Joaquin","Tomas"] [Comedia] ["Los tres chiflados", "Bonanza"])) )
	)

testGenerarSagaDePeliculasTieneLongitudCorrecta2 = TestCase (
		assertBool 
		"La longitud no es correcta al generar una saga de peliculas" 
		(3 == (length (generarSagaDePeliculasP ["Javier","Joaquin","Tomas"] [Comedia] ["Los tres chiflados", "Bonanza", "Pochoclera"])) )
	)

testGenerarSagaDePeliculasTieneLongitudCorrecta3 = TestCase (
		assertBool 
		"La longitud no es correcta al generar una saga de peliculas" 
		(0 == (length (generarSagaDePeliculasP ["Javier","Joaquin","Tomas"] [Comedia] [])) )
	)

testGenerarSagaDePeliculasTieneLongitudCorrecta4 = TestCase (
		assertBool 
		"La longitud no es correcta al generar una saga de peliculas" 
		(0 == (length (generarSagaDePeliculasP [] [Comedia] [])) )
	)

testGenerarSagaDePeliculasTieneLongitudCorrecta5 = TestCase (
		assertBool 
		"La longitud no es correcta al generar una saga de peliculas" 
		(0 == (length (generarSagaDePeliculasP [] [] [])) )
	)

nombresDePeliculasParaLaSaga = ["Star Wars I", "Star Wars II", "Star Wars III"]

testGenerarSagaDePeliculasContieneCadaNombredePelicula1 = TestCase (
		assertEqual 
		"No hay al menos una pelicula por cada nombre recibido como parametro" 
		(length nombresDePeliculasParaLaSaga) (length (generarSagaDePeliculasP ["Robert De Niro"] [Aventura] nombresDePeliculasParaLaSaga))
	)

testGenerarSagaDePeliculasContieneCadaNombredePelicula2 = TestCase (
		assertBool 
		"Las peliculas generadas en la saga no tienen los actores y/o los generos que corresponde" 
		(and[((actoresP p) == ["Robert De Niro"]) && ((generosP p) == [Aventura]) | n <- nombresDePeliculasParaLaSaga, p <- (generarSagaDePeliculasP ["Robert De Niro"] [Aventura] nombresDePeliculasParaLaSaga), n == (nombreP p)])
	)

testGenerarSagaDePeliculasContieneCadaNombredePelicula3 = TestCase (
		assertBool 
		"Las peliculas generadas en la saga no tienen el nombre que corresponde" 
		((length nombresDePeliculasParaLaSaga) == (sum [ 1 | n <- nombresDePeliculasParaLaSaga, p <- (generarSagaDePeliculasP ["Robert De Niro"] [Aventura] nombresDePeliculasParaLaSaga), n == (nombreP p)]))
	)


-- Ticket

t1 = nuevoT p1 1 False
t2 = nuevoT p2 2 False
t3 = nuevoT p3 3 False

testPeliculaCorrecta1 = TestCase (
		assertEqual 
		"El observador pelicula no devuelve el valor esperado" 
		p1 (peliculaT t1)
	)

testPeliculaCorrecta2 = TestCase (
		assertEqual 
		"El observador pelicula no devuelve el valor esperado" 
		p2 (peliculaT t2)
	)

testPeliculaCorrecta3 = TestCase (
		assertEqual 
		"El observador pelicula no devuelve el valor esperado" 
		p3 (peliculaT t3)
	)

testSalaCorrecta1 = TestCase (
		assertEqual 
		"El observador sala no devuelve el valor esperado" 
		1 (salaT t1)
	)

testSalaCorrecta2 = TestCase (
		assertEqual 
		"El observador sala no devuelve el valor esperado" 
		2 (salaT t2)
	)

testSalaCorrecta3 = TestCase (
		assertEqual 
		"El observador sala no devuelve el valor esperado" 
		3 (salaT t3)
	)

testUsado1 = TestCase (
		assertEqual 
		"El observador usado no devuelve el valor esperado" 
		False (usadoT t1)
	)

testUsado2 = TestCase (
		assertEqual 
		"El observador usado no devuelve el valor esperado" 
		False (usadoT t2)
	)

testUsado3 = TestCase (
		assertEqual 
		"El observador usado no devuelve el valor esperado" 
		False (usadoT t3)
	)

testUsado4 = TestCase (
		assertEqual 
		"El observador usado no devuelve el valor esperado" 
		True (usadoT (usarT t1))
	)

testUsado5 = TestCase (
		assertEqual 
		"El observador usado no devuelve el valor esperado" 
		True (usadoT (usarT t2))
	)

testUsado6 = TestCase (
		assertEqual 
		"El observador usado no devuelve el valor esperado" 
		True (usadoT (usarT t3))
	)

testUsado7 = TestCase (
		assertEqual 
		"El observador usado no devuelve el valor esperado" 
		True (usadoT (usarT (usarT t3)))
	)

testUsado8 = TestCase (
		assertEqual 
		"El observador usado no devuelve el valor esperado" 
		True (usadoT (usarT (usarT (usarT t3))))
	)

testUsado9 = TestCase (
		assertEqual 
		"El observador usado no devuelve el valor esperado" 
		True (usadoT (usarT (usarT (usarT (usarT (usarT (usarT t3)))))))
	)

testPeliculaMenosVistaEsValida1 = TestCase (
		assertBool 
		"La pelicula menos vista no pertenece a ninguno de los tickets pasados como parametro" 
		(any ( == peliculaMenosVistaT [t1]) [(peliculaT t1),(peliculaT t2), (peliculaT t3)])
	)

testPeliculaMenosVistaEsValida2 = TestCase (
		assertBool 
		"La pelicula menos vista no pertenece a ninguno de los tickets pasados como parametro" 
		(any ( == peliculaMenosVistaT [t1, t2]) [(peliculaT t1),(peliculaT t2), (peliculaT t3)])
	)

testPeliculaMenosVistaEsValida3 = TestCase (
		assertBool 
		"La pelicula menos vista no pertenece a ninguno de los tickets pasados como parametro" 
		(any ( == peliculaMenosVistaT [t1, t3]) [(peliculaT t1),(peliculaT t2), (peliculaT t3)])
	)

testPeliculaMenosVistaEsValida4 = TestCase (
		assertBool 
		"La pelicula menos vista no pertenece a ninguno de los tickets pasados como parametro" 
		(any ( == peliculaMenosVistaT [t2, t3]) [(peliculaT t1),(peliculaT t2), (peliculaT t3)])
	)

testPeliculaMenosVistaEsValida5 = TestCase (
		assertBool 
		"La pelicula menos vista no pertenece a ninguno de los tickets pasados como parametro" 
		(any ( == peliculaMenosVistaT [t1, t2, t3]) [(peliculaT t) | t <- [t1, t2, t3]])
	)

testPeliculaMenosVistaEsLaDelTicketMenosUsado1 = TestCase (
		assertBool
		"La pelicula menos vista no es aquella cuyo ticket tiene el menor uso de los tickets pasados como parametro" 
		(elem (peliculaMenosVistaT [t1, t2, t3]) [p1, p2, p3]) 
	)

t4 = (usarT t1)
t5 = (usarT t4)
t6 = (usarT t5)
t7 = (usarT t2)

testPeliculaMenosVistaEsLaDelTicketMenosUsado2 = TestCase (
		assertEqual
		"La pelicula menos vista no es aquella cuyo ticket tiene el menor uso de los tickets pasados como parametro" 
		(peliculaMenosVistaT [t1, t2, t3, t4, t5, t6, t7]) p3 
	)

testPeliculaMenosVistaEsLaDelTicketMenosUsado3 = TestCase (
		assertEqual
		"La pelicula menos vista no es aquella cuyo ticket tiene el menor uso de los tickets pasados como parametro" 
		(peliculaMenosVistaT [t3, t4, t5, t6, t7]) p3
	)

testPeliculaMenosVistaEsLaDelTicketMenosUsado4 = TestCase (
		assertEqual
		"La pelicula menos vista no es aquella cuyo ticket tiene el menor uso de los tickets pasados como parametro" 
		(peliculaMenosVistaT [t5, t6, t7]) p2
	)

t8 = (usarT t6)
t9 = (usarT t7)

testPeliculaMenosVistaEsLaDelTicketMenosUsado5 = TestCase (
		assertBool
		"La pelicula menos vista no es aquella cuyo ticket tiene el menor uso de los tickets pasados como parametro" 
		(elem (peliculaMenosVistaT [t5, t6, t7, t9]) [p2, p1])
	)

testPeliculaMenosVistaEsLaDelTicketMenosUsado6 = TestCase (
		assertEqual
		"La pelicula menos vista no es aquella cuyo ticket tiene el menor uso de los tickets pasados como parametro" 
		(peliculaMenosVistaT [t1, t2, t4, t5, t6, t7, t8, t9]) p2
	)

testPeliculaMenosVistaEsLaDelTicketMenosUsado7 = TestCase (
		assertEqual
		"La pelicula menos vista no es aquella cuyo ticket tiene el menor uso de los tickets pasados como parametro" 
		(peliculaMenosVistaT listaCompletaDeTickets) p3
	)

testTodosLosTicketsParaLaMismaSala1 = TestCase (
		assertEqual
		"Error al usar todosLosTicketsParaLaMismaSala" 
		True (todosLosTicketsParaLaMismaSalaT [t1, t4])
	)

testTodosLosTicketsParaLaMismaSala2 = TestCase (
		assertEqual
		"Error al usar todosLosTicketsParaLaMismaSala" 
		True (todosLosTicketsParaLaMismaSalaT [t1, t4, t5, t6])
	)

testTodosLosTicketsParaLaMismaSala3 = TestCase (
		assertEqual
		"Error al usar todosLosTicketsParaLaMismaSala" 
		True (todosLosTicketsParaLaMismaSalaT [t1])
	)

testTodosLosTicketsParaLaMismaSala4 = TestCase (
		assertEqual
		"Error al usar todosLosTicketsParaLaMismaSala" 
		True (todosLosTicketsParaLaMismaSalaT [])
	)

testTodosLosTicketsParaLaMismaSala5 = TestCase (
		assertEqual
		"Error al usar todosLosTicketsParaLaMismaSala" 
		False (todosLosTicketsParaLaMismaSalaT [t1, t2])
	)

testTodosLosTicketsParaLaMismaSala6 = TestCase (
		assertEqual
		"Error al usar todosLosTicketsParaLaMismaSala" 
		False (todosLosTicketsParaLaMismaSalaT [t1, t2, t3])
	)

primerosTresTickets = [t1, t2, t3]
listaCompletaDeTickets = [t1, t2, t3, t4, t5, t6, t7, t8, t9]

testTodosLosTicketsParaLaMismaSala7 = TestCase (
		assertEqual
		"Error al usar todosLosTicketsParaLaMismaSala" 
		False (todosLosTicketsParaLaMismaSalaT listaCompletaDeTickets)
	)

testCambiarSalaDejaLaListaConIgualLongitud1 = TestCase (
		assertEqual
		"Error al usar todosLosTicketsParaLaMismaSala" 
		(length (listaCompletaDeTickets)) (length (cambiarSalaT listaCompletaDeTickets 1 3))
	)

testCambiarSalaDejaLaListaConIgualLongitud2 = TestCase (
		assertEqual
		"Error al usar todosLosTicketsParaLaMismaSala" 
		(length (primerosTresTickets)) (length (cambiarSalaT primerosTresTickets 1 3))
	)

testCambiarSalaDejaLaListaConIgualLongitud3 = TestCase (
		assertEqual
		"Error al usar todosLosTicketsParaLaMismaSala" 
		(length ([t1])) (length (cambiarSalaT [t1] 1 3))
	)

testCambiarSalaDejaLaListaConIgualLongitud4 = TestCase (
		assertEqual
		"Error al usar todosLosTicketsParaLaMismaSala" 
		(length ([])) (length (cambiarSalaT [] 1 3))
	)

testOtrasNoCambian1 = TestCase (
		assertEqual
		"Error al usar todosLosTicketsParaLaMismaSala" 
		(salaT t1) (salaT ((cambiarSalaT [t1, t2, t3, t4] 2 3)!!0))
	)

testOtrasNoCambian2 = TestCase (
		assertEqual
		"Error al usar todosLosTicketsParaLaMismaSala" 
		(salaT t4) (salaT ((cambiarSalaT [t1, t2, t3, t4] 2 3)!!3))
	)

testOtrasNoCambian3 = TestCase (
		assertEqual
		"Error al usar todosLosTicketsParaLaMismaSala" 
		(salaT t2) (salaT ((cambiarSalaT [t1, t2, t3, t4] 1 2)!!1))
	)

testViejaReemplazada1 = TestCase (
		assertEqual
		"Error al usar todosLosTicketsParaLaMismaSala" 
		3 (salaT ((cambiarSalaT [t1, t2, t3, t4] 2 3)!!1))
	)

testViejaReemplazada2 = TestCase (
		assertEqual
		"Error al usar todosLosTicketsParaLaMismaSala" 
		2 (salaT ((cambiarSalaT [t1, t2, t3, t4] 1 2)!!0))
	)

testViejaReemplazada3 = TestCase (
		assertEqual
		"Error al usar todosLosTicketsParaLaMismaSala" 
		2 (salaT ((cambiarSalaT [t1, t2, t3, t4] 1 2)!!3))
	)


-- Cine

c1 = nuevoC "Royal"
c2 = nuevoC "Arteplex"
c3 = nuevoC "Abasto"

testNuevoCineEnOrden1 = TestCase (
		assertBool
		"El nuevo cine no se abre correctamente" 
		(("Royal" == (nombreC c1)) && ((length (peliculasC c1)) == 0) && ((length (salasC c1)) == 0))
	)

testNuevoCineEnOrden2 = TestCase (
		assertBool
		"El nuevo cine no se abre correctamente" 
		(("Arteplex" == (nombreC c2)) && ((length (peliculasC c2)) == 0) && ((length (salasC c2)) == 0))
	)

testNuevoCineEnOrden3 = TestCase (
		assertBool
		"El nuevo cine no se abre correctamente" 
		(("Abasto" == (nombreC c3)) && ((length (peliculasC c3)) == 0) && ((length (salasC c3)) == 0))
	)

c4 = abrirSalaC (c1) 1
c5 = abrirSalaC (abrirSalaC (abrirSalaC (c2) 1) 2) 3
c6 = abrirSalaC (abrirSalaC (abrirSalaC (abrirSalaC (c3) 1) 2) 3) 4

testAbrirSalaPreservaElNombre1 = TestCase (
		assertEqual
		"Tenemos un problema: abrir una sala cambia el nombre del cine" 
		"Royal" (nombreC c4)
	)

testAbrirSalaPreservaElNombre2 = TestCase (
		assertEqual
		"Tenemos un problema: abrir una sala cambia el nombre del cine" 
		"Arteplex" (nombreC c5)
	)

testAbrirSalaPreservaElNombre3 = TestCase (
		assertEqual
		"Tenemos un problema: abrir una sala cambia el nombre del cine" 
		"Abasto" (nombreC c6)
	)

testAbrirSalaDejaLasSalasCorresponientes1 = TestCase (
		assertBool
		"Abrir sala deja las salas abiertas como parte del cine y agrega al cine las salas a abir" 
		(mismos [1,2,3,4,5] (salasC (abrirSalaC c6 5)))
	)

testAbrirSalaDejaLasSalasCorresponientes2 = TestCase (
		assertBool
		"Abrir sala deja las salas abiertas como parte del cine y agrega al cine las salas a abir" 
		(mismos [1,5] (salasC (abrirSalaC c4 5)))
	)

c7 = agregarPeliculaC c4 p1 1
c8 = agregarPeliculaC (agregarPeliculaC (agregarPeliculaC c5 p1 1) p2 2) p3 3
c9 = agregarPeliculaC (agregarPeliculaC (agregarPeliculaC (agregarPeliculaC c6 p2 1) p4 2) p3 3) p1 4

testAbrirSalaPreservaLasPeliculas1 = TestCase (
		assertBool
		"Tenemos un problema: abrir una sala cambia las peliculas del cine" 
		(mismos (peliculasC c7) (peliculasC (abrirSalaC c7 9)))
	)

testAbrirSalaPreservaLasPeliculas2 = TestCase (
		assertBool
		"Tenemos un problema: abrir una sala cambia las peliculas del cine" 
		(mismos (peliculasC c8) (peliculasC (abrirSalaC c8 9)))
	)

testAbrirSalaPreservaLasPeliculas3 = TestCase (
		assertBool
		"Tenemos un problema: abrir una sala cambia las peliculas del cine" 
		(mismos (peliculasC c9) (peliculasC (abrirSalaC c9 9)))
	)

testAbrirSalaPreservaLasPeliculasEnLaSalaEnLaQueEstaban1 = TestCase (
		assertBool
		"Tenemos un problema: abrir una sala cambia las salas de las peliculas del cine" 
		(and [ ((salaC (abrirSalaC c7 9) p ) == (salaC c7 p)) | p <- (peliculasC c7)])
	)

testAbrirSalaPreservaLasPeliculasEnLaSalaEnLaQueEstaban2 = TestCase (
		assertBool
		"Tenemos un problema: abrir una sala cambia las salas de las peliculas del cine" 
		(and [ ((salaC (abrirSalaC c8 9) p ) == (salaC c8 p)) | p <- (peliculasC c8)])
	)

testAbrirSalaPreservaLasPeliculasEnLaSalaEnLaQueEstaban3 = TestCase (
		assertBool
		"Tenemos un problema: abrir una sala cambia las salas de las peliculas del cine" 
		(and [ ((salaC (abrirSalaC c9 9) p ) == (salaC c9 p)) | p <- (peliculasC c9)])
	)

testAbrirSalaPreservaLasPeliculasEnLaSalaEnLaQueEstaban4 = TestCase (
		assertBool
		"Tenemos un problema: abrir una sala cambia las salas de las peliculas del cine" 
		(and [ ((salaC (abrirSalaC c1 9) p ) == (salaC c1 p)) | p <- (peliculasC c1)])
	)

testAbrirSalaPreservaLasPeliculasEnLaSalaEnLaQueEstaban5 = TestCase (
		assertBool
		"Tenemos un problema: abrir una sala cambia las salas de las peliculas del cine" 
		(and [ ((salaC (abrirSalaC c2 9) p ) == (salaC c2 p)) | p <- (peliculasC c2)])
	)

testAbrirSalaPreservaLasPeliculasEnLaSalaEnLaQueEstaban6 = TestCase (
		assertBool
		"Tenemos un problema: abrir una sala cambia las salas de las peliculas del cine" 
		(and [ ((salaC (abrirSalaC c3 9) p ) == (salaC c3 p)) | p <- (peliculasC c3)])
	)

c10 = fst (venderTicketC c7 p1)
c11 = fst (venderTicketC (fst (venderTicketC c8 p1)) p2)
c12 = fst (venderTicketC (fst (venderTicketC (fst (venderTicketC (fst (venderTicketC (fst (venderTicketC (fst (venderTicketC c9 p2)) p2)) p1)) p2)) p3)) p2)

testAbrirSalaPreservaLosEspectadoresOriginales1 = TestCase (
		assertEqual
		"Tenemos un problema: abrir una sala cambia los espectadores del cine" 
		(espectadoresC c12 2) (espectadoresC (abrirSalaC c12 9) 2)
	)

testAbrirSalaPreservaLosEspectadoresOriginales2 = TestCase (
		assertEqual
		"Tenemos un problema: abrir una sala cambia los espectadores del cine" 
		(espectadoresC c11 2) (espectadoresC (abrirSalaC c11 9) 2)
	)

testAbrirSalaPreservaLosEspectadoresOriginales3 = TestCase (
		assertEqual
		"Tenemos un problema: abrir una sala cambia los espectadores del cine" 
		(espectadoresC c10 1) (espectadoresC (abrirSalaC c10 9) 1)
	)

testAbrirSalaPreservaLosEspectadoresOriginales4 = TestCase (
		assertEqual
		"Tenemos un problema: abrir una sala cambia los espectadores del cine" 
		(espectadoresC c9 3) (espectadoresC (abrirSalaC c9 9) 3)
	)

testAbrirSalaPreservaLosTicketsOriginales1 = TestCase (
		assertEqual
		"Tenemos un problema: abrir una sala cambia los Tickets del cine" 
		(ticketsVendidosC c12) (ticketsVendidosC (abrirSalaC c12 9))
	)

testAbrirSalaPreservaLosTicketsOriginales2 = TestCase (
		assertEqual
		"Tenemos un problema: abrir una sala cambia los Tickets del cine" 
		(ticketsVendidosC c11) (ticketsVendidosC (abrirSalaC c11 9))
	)

testAbrirSalaPreservaLosTicketsOriginales3 = TestCase (
		assertEqual
		"Tenemos un problema: abrir una sala cambia los Tickets del cine" 
		(ticketsVendidosC c10) (ticketsVendidosC (abrirSalaC c10 9))
	)

testAbrirSalaPreservaLosTicketsOriginales4 = TestCase (
		assertEqual
		"Tenemos un problema: abrir una sala cambia los Tickets del cine" 
		(ticketsVendidosC c9) (ticketsVendidosC (abrirSalaC c9 9))
	)

-- Recuerdatorio (variables definidas mas arriba)
--c7 = agregarPeliculaC c4 1 p1
--c8 = agregarPeliculaC (agregarPeliculaC (agregarPeliculaC c5 1 p1) 2 p2) 3 p3
--c9 = agregarPeliculaC (agregarPeliculaC (agregarPeliculaC (agregarPeliculaC c6 1 p2) 2 p4) 3 p3) 4 p1

testAgregarPeliculaPreservaElNombre1 = TestCase (
		assertEqual
		"Tenemos un problema: agregar una pelicula al cine cambia el nombre del cine" 
		"Royal" (nombreC c7)
	)

testAgregarPeliculaPreservaElNombre2 = TestCase (
		assertEqual
		"Tenemos un problema: agregar una pelicula al cine cambia el nombre del cine" 
		"Arteplex" (nombreC c8)
	)

testAgregarPeliculaPreservaElNombre3 = TestCase (
		assertEqual
		"Tenemos un problema: agregar una pelicula al cine cambia el nombre del cine" 
		"Abasto" (nombreC c9)
	)

testAgregarPeliculaDejaLasSalasCorresponientes1 = TestCase (
		assertBool
		"Agregar una pelicula al cine no deja las salas como estaban" 
		(mismos [1,2,3] (salasC (agregarPeliculaC c5 p1 1)))
	)

testAgregarPeliculaDejaLasSalasCorresponientes2 = TestCase (
		assertBool
		"Agregar una pelicula al cine no deja las salas como estaban" 
		(mismos [1,2,3,4] (salasC (agregarPeliculaC c6 p2 2)))
	)

testAgregarPeliculaPreservaLosEspectadoresOriginales1 = TestCase (
		assertEqual
		"Tenemos un problema: agregar una pelicula al cine cambia los espectadores del cine" 
		(espectadoresC c12 2) (espectadoresC (agregarPeliculaC c12 p2 9) 2)
	)

testAgregarPeliculaPreservaLosEspectadoresOriginales2 = TestCase (
		assertEqual
		"Tenemos un problema: agregar una pelicula al cine cambia los espectadores del cine" 
		(espectadoresC c11 2) (espectadoresC (agregarPeliculaC c11 p2 9) 2)
	)

testAgregarPeliculaPreservaLosEspectadoresOriginales3 = TestCase (
		assertEqual
		"Tenemos un problema: agregar una pelicula al cine cambia los espectadores del cine" 
		(espectadoresC c10 1) (espectadoresC (agregarPeliculaC c10 p2 9) 1)
	)

testAgregarPeliculaPreservaLosEspectadoresOriginales4 = TestCase (
		assertEqual
		"Tenemos un problema: agregar una pelicula al cine cambia los espectadores del cine" 
		(espectadoresC c9 3) (espectadoresC (agregarPeliculaC c9 p2 9) 3)
	)

testAgregarPeliculaPreservaLosTicketsOriginales = TestCase (
		assertEqual
		"Tenemos un problema: agregar una pelicula al cine cambia los Tickets del cine" 
		(ticketsVendidosC c9) (ticketsVendidosC (agregarPeliculaC c6 p3 1))
	)

c20 = nuevoC "Hoyts"
c21 = abrirSalaC c20 1
c22 = abrirSalaC c21 2
c23 = agregarPeliculaC c22 p1 1
c24 = agregarPeliculaC c23 p2 2
c25 = abrirSalaC c22 3

testAgregarPeliculaAgregaPeliculaALasPeliculasExistentesDelCine = TestCase (
		assertBool
		"Agregar una pelicula no agrega la pelicula a las peliculas existentes del cine"
		(mismos (p3:(peliculasC c25)) (peliculasC (agregarPeliculaC c25 p3 3)))
	)

testAgregarPeliculaAgregaLaPeliculaEnLaSalaEspecificada1 = TestCase (
		assertEqual
		"Agregar una pelicula no agrega la pelicula en la sala indicada"
		3 (salaC (agregarPeliculaC c25 p3 3) p3)
	)

testAgregarPeliculaAgregaLaPeliculaEnLaSalaEspecificada2 = TestCase (
		assertEqual
		"Agregar una pelicula no agrega la pelicula en la sala indicada"
		2 (salaC (agregarPeliculaC c25 p3 2) p3)
	)

testAgregarPeliculaAgregaLaPeliculaEnLaSalaEspecificada3 = TestCase (
		assertEqual
		"Agregar una pelicula no agrega la pelicula en la sala indicada"
		1 (salaC (agregarPeliculaC c25 p1 1) p1)
	)

testCerrarSalaPreservaElNombre1 = TestCase (
		assertEqual
		"Tenemos un problema: cerrar una sala sin pelicula del cine cambia el nombre del cine" 
		"Hoyts" (nombreC (cerrarSalaC c25 3))
	)

testCerrarSalaPreservaElNombre2 = TestCase (
		assertEqual
		"Tenemos un problema: cerrar una sala con pelicula del cine cambia el nombre del cine" 
		"Hoyts" (nombreC (cerrarSalaC c25 2))
	)

testCerrarSalaPreservaElNombre3 = TestCase (
		assertEqual
		"Tenemos un problema: cerrar una sala con pelicula del cine cambia el nombre del cine" 
		"Hoyts" (nombreC (cerrarSalaC c25 1))
	)

testCerrarSalaSacaLaSalaDelCine1 = TestCase (
		assertBool
		"Cerrar una sala del cine no elimina la sala del cine" 
		 (mismos (salasC c25) (1:(salasC (cerrarSalaC c25 1))))
	)

testCerrarSalaSacaLaSalaDelCine2 = TestCase (
		assertBool
		"Cerrar una sala del cine no elimina la sala del cine" 
		 (mismos (salasC c25) (2:(salasC (cerrarSalaC c25 2))))
	)

testCerrarSalaSacaLaSalaDelCine3 = TestCase (
		assertBool
		"Cerrar una sala del cine no elimina la sala del cine" 
		 (mismos (salasC c25) (3:(salasC (cerrarSalaC c25 3))))
	)
c26 = abrirSalaC c24 3

testCerrarSalaMantieneLasPeliculasAExcepcionDeAquellaEnLaSalaCerrada1 = TestCase (
		assertBool
		"No es el caso que cerrar una sala mantienga las peliculas del cine a excepcion de aquella pelicula en la sala que fue cerrada" 
		 (mismos (peliculasC c26) (peliculasC (cerrarSalaC c26 3)))
	)

testCerrarSalaMantieneLasPeliculasAExcepcionDeAquellaEnLaSalaCerrada2 = TestCase (
		assertBool
		"No es el caso que cerrar una sala mantienga las peliculas del cine a excepcion de aquella pelicula en la sala que fue cerrada" 
		 (mismos (peliculasC c26) (p2:(peliculasC (cerrarSalaC c26 2))))
	)

testCerrarSalaMantieneLasPeliculasAExcepcionDeAquellaEnLaSalaCerrada3 = TestCase (
		assertBool
		"No es el caso que cerrar una sala mantienga las peliculas del cine a excepcion de aquella pelicula en la sala que fue cerrada" 
		(mismos (peliculasC c26) (p1:(peliculasC (cerrarSalaC c26 1))))
	)

testCerrarSalaMantieneLasPeliculasEnLaMismaSala1 = TestCase (
		assertEqual
		"Cerrar una sala no mantiene las peliculas del cine en su sala original" 
		(salaC c26 p1) (salaC (cerrarSalaC c26 3) p1)
	)

testCerrarSalaMantieneLasPeliculasEnLaMismaSala2 = TestCase (
		assertEqual
		"Cerrar una sala no mantiene las peliculas del cine en su sala original" 
		(salaC c26 p2) (salaC (cerrarSalaC c26 3) p2)
	)

testCerrarSalaMantieneLasPeliculasEnLaMismaSala3 = TestCase (
		assertEqual
		"Cerrar una sala no mantiene las peliculas del cine en su sala original" 
		(salaC c26 p1) (salaC (cerrarSalaC c26 2) p1)
	)

testCerrarSalaMantieneLasPeliculasEnLaMismaSala4 = TestCase (
		assertEqual
		"Cerrar una sala no mantiene las peliculas del cine en su sala original" 
		(salaC c26 p2) (salaC (cerrarSalaC c26 1) p2)
	)

c27 = fst (venderTicketC c26 p1)
c28 = fst (venderTicketC c27 p1)
c29 = fst (venderTicketC c28 p1)
c30 = fst (venderTicketC c29 p2)

testCerrarSalaMantieneLosEspectadoresDeLaSalaOriginal1 = TestCase (
		assertEqual
		"Cerrar una sala no mantiene los espectadores del cine en su sala original" 
		(espectadoresC c30 1) (espectadoresC (cerrarSalaC c30 2) 1)
	)

testCerrarSalaMantieneLosEspectadoresDeLaSalaOriginal2 = TestCase (
		assertEqual
		"Cerrar una sala no mantiene los espectadores del cine en su sala original" 
		(espectadoresC c30 2) (espectadoresC (cerrarSalaC c30 1) 2)
	)

testCerrarSalaMantieneLosEspectadoresDeLaSalaOriginal3 = TestCase (
		assertEqual
		"Cerrar una sala no mantiene los espectadores del cine en su sala original" 
		(espectadoresC c30 1) (espectadoresC (cerrarSalaC c12 3) 1)
	)

testCerrarSalaMantieneLosEspectadoresDeLaSalaOriginal4 = TestCase (
		assertEqual
		"Cerrar una sala no mantiene los espectadores del cine en su sala original" 
		(espectadoresC c30 2) (espectadoresC (cerrarSalaC c12 3) 2)
	)

testCerrarSalaMantieneLosTickets1 = TestCase (
		assertBool
		"Cerrar una sala no mantiene los tickets del cine original" 
		(mismos (ticketsVendidosC c30) (ticketsVendidosC (cerrarSalaC c30 3)))
	)

testCerrarSalaMantieneLosTickets2 = TestCase (
		assertBool
		"Cerrar una sala no mantiene los tickets del cine original" 
		(mismos (ticketsVendidosC c30) (ticketsVendidosC (cerrarSalaC c30 2)))
	)

testCerrarSalaMantieneLosTickets3 = TestCase (
		assertBool
		"Cerrar una sala no mantiene los tickets del cine original" 
		(mismos (ticketsVendidosC c30) (ticketsVendidosC (cerrarSalaC c30 1)))
	)



c31 = fst (venderTicketC c30 p2)
c32 = agregarPeliculaC c31 p3 3
c33 = abrirSalaC c32 4
c34 = agregarPeliculaC c33 p4 4
--la sala 3 sigue vacia

testCerrarSalasMantieneElNombreDelCine1 = TestCase (
		assertBool
		"Cerrar salas de un cine no mantiene el nomrbre del cine original" 
		(mismos (nombreC c34) (nombreC (cerrarSalasC c34 1)))
	)

testCerrarSalasMantieneElNombreDelCine2 = TestCase (
		assertBool
		"Cerrar salas de un cine no mantiene el nomrbre del cine original" 
		(mismos (nombreC c34) (nombreC (cerrarSalasC c34 2)))
	)

testCerrarSalasMantieneElNombreDelCine3 = TestCase (
		assertBool
		"Cerrar salas de un cine no mantiene el nomrbre del cine original" 
		(mismos (nombreC c34) (nombreC (cerrarSalasC c34 3)))
	)

testCerrarSalasMantieneElNombreDelCine4 = TestCase (
		assertBool
		"Cerrar salas de un cine no mantiene el nomrbre del cine original" 
		(mismos (nombreC c34) (nombreC (cerrarSalasC c34 4)))
	)

--recondando...
--c20 = nuevoC "Hoyts"
--c21 = abrirSalaC c20 1
--c22 = abrirSalaC c21 2
--c23 = agregarPeliculaC c22 1 p1
--c24 = agregarPeliculaC c23 2 p2
--c26 = abrirSalaC c24 3
--c27 = fst (venderTicketC c26 p1)
--c28 = fst (venderTicketC c27 p1)
--c29 = fst (venderTicketC c28 p1)
--c30 = fst (venderTicketC c29 p2)
--c31 = fst (venderTicketC c30 p2)
--c32 = agregarPeliculaC c31 3 p3
--c33 = abrirSalaC c32 4
--c34 = agregarPeliculaC c33 4 p4

t27 = snd (venderTicketC c26 p1)
t28 = snd (venderTicketC c27 p1)
t29 = snd (venderTicketC c28 p1)
t30 = snd (venderTicketC c29 p2)
t31 = snd (venderTicketC c30 p2)

c35 = fst (ingresarASalaC c34 1 t27)
c36 = fst (ingresarASalaC c35 1 t28)
c37 = fst (ingresarASalaC c36 1 t29)
c38 = fst (ingresarASalaC c37 2 t30)
c39 = fst (ingresarASalaC c38 2 t31)

testCerrarSalasSacaLaSalasCorrespondientesDelCine1 = TestCase (
		assertBool
		"Cerrar salas del cine no elimina la salas que deberia del cine" 
		 (mismos [1,2] (salasC (cerrarSalasC c39 1)))
	)

testCerrarSalasSacaLaSalasCorrespondientesDelCine2 = TestCase (
		assertBool
		"Cerrar salas del cine no elimina la salas que deberia del cine" 
		 (mismos [1,2] (salasC (cerrarSalasC c39 2)))
	)

testCerrarSalasSacaLaSalasCorrespondientesDelCine3 = TestCase (
		assertBool
		"Cerrar salas del cine no elimina la salas que deberia del cine" 
		 (mismos [1] (salasC (cerrarSalasC c39 3)))
	)

testCerrarSalasSacaLaSalasCorrespondientesDelCine4 = TestCase (
		assertBool
		"Cerrar salas del cine no elimina la salas que deberia del cine" 
		 (mismos [] (salasC (cerrarSalasC c39 4)))
	)

testCerrarSalasSacaLaSalasCorrespondientesDelCine5 = TestCase (
		assertBool
		"Cerrar salas del cine no elimina la salas que deberia del cine" 
		 (mismos [] (salasC (cerrarSalasC c39 5)))
	)

testCerrarSalasSacaLaSalasCorrespondientesDelCine6 = TestCase (
		assertBool
		"Cerrar salas del cine no elimina la salas que deberia del cine" 
		 (mismos [1,2,3,4] (salasC (cerrarSalasC c39 0)))
	)

testCerrarSalasDejaLasPeliculasEnSalasActivasYRemueveLasDeAquellasSalasCerradas1 = TestCase (
		assertBool
		"Cerrar salas del cine no es coherente con las peliculas que deja en cartel" 
		 (mismos [] (salasC (cerrarSalasC c39 5)))
	)

testCerrarSalasDejaLasPeliculasEnSalasActivasYRemueveLasDeAquellasSalasCerradas2 = TestCase (
		assertBool
		"Cerrar salas del cine no es coherente con las peliculas que deja en cartel" 
		 (mismos [] (salasC (cerrarSalasC c39 4)))
	)

testCerrarSalasDejaLasPeliculasEnSalasActivasYRemueveLasDeAquellasSalasCerradas3 = TestCase (
		assertBool
		"Cerrar salas del cine no es coherente con las peliculas que deja en cartel" 
		 (mismos [1] (salasC (cerrarSalasC c39 3)))
	)

testCerrarSalasDejaLasPeliculasEnSalasActivasYRemueveLasDeAquellasSalasCerradas4 = TestCase (
		assertBool
		"Cerrar salas del cine no es coherente con las peliculas que deja en cartel" 
		 (mismos [1,2] (salasC (cerrarSalasC c39 2)))
	)

testCerrarSalasDejaLasPeliculasEnSalasActivasYRemueveLasDeAquellasSalasCerradas5 = TestCase (
		assertBool
		"Cerrar salas del cine no es coherente con las peliculas que deja en cartel" 
		 (mismos [1,2] (salasC (cerrarSalasC c39 1)))
	)

testCerrarSalasDejaLasPeliculasEnSalasActivasYRemueveLasDeAquellasSalasCerradas6 = TestCase (
		assertBool
		"Cerrar salas del cine no es coherente con las peliculas que deja en cartel" 
		 (mismos [1,2,3,4] (salasC (cerrarSalasC c39 0)))
	)

testCerrarSalasDeLaCadenaDejaLaMismaCantidadDeCines1 = TestCase (
		assertEqual
		"Error: Cerrar las salas de la cadena no devuelve la misma cantidad de cines que recibe como parametro"
		(length [c35, c36]) (length (cerrarSalasDeLaCadenaC [c35, c36] 0 ))
	)

testCerrarSalasDeLaCadenaDejaLaMismaCantidadDeCines2 = TestCase (
		assertEqual
		"Error: Cerrar las salas de la cadena no devuelve la misma cantidad de cines que recibe como parametro"
		(length [c35, c36]) (length (cerrarSalasDeLaCadenaC [c35, c36] 1 ))
	)

testCerrarSalasDeLaCadenaDejaLaMismaCantidadDeCines3 = TestCase (
		assertEqual
		"Error: Cerrar las salas de la cadena no devuelve la misma cantidad de cines que recibe como parametro"
		(length [c35, c36]) (length (cerrarSalasDeLaCadenaC [c35, c36] 2 ))
	)

testCerrarSalasDeLaCadenaDejaLaMismaCantidadDeCines4 = TestCase (
		assertEqual
		"Error: Cerrar las salas de la cadena no devuelve la misma cantidad de cines que recibe como parametro"
		(length [c35, c36]) (length (cerrarSalasDeLaCadenaC [c35, c36] 3 ))
	)

testCerrarSalasDeLaCadenaDejaLaMismaCantidadDeCines5 = TestCase (
		assertEqual
		"Error: Cerrar las salas de la cadena no devuelve la misma cantidad de cines que recibe como parametro"
		(length [c35, c36, c37, c38, c39]) (length (cerrarSalasDeLaCadenaC [c35, c36, c37, c38, c39] 0 ))
	)

testCerrarSalasDeLaCadenaDejaLaMismaCantidadDeCines6 = TestCase (
		assertEqual
		"Error: Cerrar las salas de la cadena no devuelve la misma cantidad de cines que recibe como parametro"
		(length [c35, c36, c37, c38, c39]) (length (cerrarSalasDeLaCadenaC [c35, c36, c37, c38, c39] 1 ))
	)

testCerrarSalasDeLaCadenaDejaLaMismaCantidadDeCines7 = TestCase (
		assertEqual
		"Error: Cerrar las salas de la cadena no devuelve la misma cantidad de cines que recibe como parametro"
		(length [c35, c36, c37, c38, c39]) (length (cerrarSalasDeLaCadenaC [c35, c36, c37, c38, c39] 2 ))
	)

testCerrarSalasDeLaCadenaDejaLaMismaCantidadDeCines8 = TestCase (
		assertEqual
		"Error: Cerrar las salas de la cadena no devuelve la misma cantidad de cines que recibe como parametro"
		(length [c35, c36, c37, c38, c39]) (length (cerrarSalasDeLaCadenaC [c35, c36, c37, c38, c39] 3 ))
	)

testCerrarSalasDeLaCadenaDejaLosMismosCinesRespetandoLaCota1 = TestCase (
		assertEqual
		"Error: Cerrar las salas de la cadena no devulve los cines con su nombre correspondiente"
		1 (length ([c | c <- (cerrarSalasDeLaCadenaC [c35, c10, c11, c12] 1), ((nombreC c) == (nombreC c35))]))
	)

testCerrarSalasDeLaCadenaDejaLosMismosCinesRespetandoLaCota2 = TestCase (
		assertEqual
		"Error: Cerrar las salas de la cadena no devulve los cines con su nombre correspondiente"
		2 (length ([c | c <- (cerrarSalasDeLaCadenaC [c35, c10, c35, c12] 1), ((nombreC c) == (nombreC c35))]))
	)

testCerrarSalasDeLaCadenaDejaLosMismosCinesRespetandoLaCota3 = TestCase (
		assertEqual
		"Error: Cerrar las salas de la cadena no devulve los cines con su nombre correspondiente"
		4 (length ([c | c <- (cerrarSalasDeLaCadenaC [c35, c35, c35, c35] 1), ((nombreC c) == (nombreC c35))]))
	)


testCerrarSalasDeLaCadenaDejaLosMismosCinesRespetandoLaCota4 = TestCase (
		assertEqual
		"Error: Cerrar las salas de la cadena no devulve los cines con sus salas correspondiente"
		[[], [], [], []] [salasC c | c <- (cerrarSalasDeLaCadenaC [c35, c10, c11, c12] 100)]
	)

testCerrarSalasDeLaCadenaDejaLosMismosCinesRespetandoLaCota5 = TestCase (
		assertEqual
		"Error: Cerrar las salas de la cadena no devulve los cines con sus salas correspondiente"
		[[], [], [], [], []] [salasC c | c <- (cerrarSalasDeLaCadenaC [c35, c36, c37, c38, c39] 100)]
	)

testCerrarSalasDeLaCadenaDejaLosMismosCinesRespetandoLaCota6 = TestCase (
		assertBool
		"Error: Cerrar las salas de la cadena no devulve los cines con sus salas correspondiente"
		(mismos [1,2,3,4] ([(salasC c) | c <- (cerrarSalasDeLaCadenaC [c35] 0)]!!0))
	)

testCerrarSalasDeLaCadenaDejaLosMismosCinesRespetandoLaCota7 = TestCase (
		assertBool
		"Error: Cerrar las salas de la cadena no devulve los cines con sus salas correspondiente"
		(mismos [1,2,3,4] ([(salasC c) | c <- (cerrarSalasDeLaCadenaC [c36] 0)]!!0))
	)

testPelicula1 = TestCase (
		assertEqual 
		"El observador pelicula no devuelve el valor esperado" 
		[] (peliculasC (c1))
	)

testPelicula2 = TestCase (
		assertEqual 
		"El observador pelicula no devuelve el valor esperado" 
		[] (peliculasC (c5))
	)

testPelicula3 = TestCase (
		assertEqual 
		"El observador pelicula no devuelve el valor esperado" 
		[p1] (peliculasC (c10))
	)

testPelicula4 = TestCase (
		assertBool
		"El observador pelicula no devuelve el valor esperado" 
		(mismos [p1, p2, p3, p4] (peliculasC (c35)))
	)

--c35 = fst (ingresarASalaC c34 1 t27)
--c36 = fst (ingresarASalaC c35 1 t28)
--c37 = fst (ingresarASalaC c36 1 t29)
--c38 = fst (ingresarASalaC c37 2 t30)
--c39 = fst (ingresarASalaC c38 2 t31)

testIngresarASala1 = TestCase (
		assertEqual
		"Error: al ingresar a una sala cambia el nombre del cine"
		"Hoyts" (nombreC c35)
	)

testIngresarASala2 = TestCase (
		assertBool
		"Error: al ingresar a una sala cambian las salas del cine"
		(mismos (salasC c38) (salasC c39))
	)

testIngresarASala3 = TestCase (
		assertBool
		"Error: al ingresar a una sala cambian las salas del cine"
		(mismos (salasC c35) (salasC c39))
	)

testIngresarASala4 = TestCase (
		assertBool
		"Error: al ingresar a una sala cambian las salas del cine"
		(mismos (salasC c34) (salasC c37))
	)

testIngresarASala5 = TestCase (
		assertBool
		"Error: al ingresar a una sala cambian las peliculas del cine"
		(mismos (salasC c34) (salasC c37))
	)

testIngresarASala6 = TestCase (
		assertBool
		"Error: al ingresar a una sala cambian las peliculas del cine"
		(mismos (peliculasC c38) (peliculasC c39))
	)

testIngresarASala7 = TestCase (
		assertBool
		"Error: al ingresar a una sala cambian las peliculas del cine"
		(mismos (peliculasC c35) (peliculasC c39))
	)

testIngresarASala8 = TestCase (
		assertBool
		"Error: al ingresar a una sala cambian las peliculas del cine"
		(mismos (peliculasC c34) (peliculasC c37))
	)

testIngresarASala9 = TestCase (
		assertBool
		"Error: al ingresar a una sala cambian las peliculas del cine"
		(mismos (peliculasC c34) (peliculasC c37))
	)


testIngresarASala10 = TestCase (
		assertEqual
		"Error: al ingresar a una sala cambia la sala asignada a una pelicula del cine"
		4 (salaC c34 ((peliculasC c34)!!0))
	)

testIngresarASala11 = TestCase (
		assertEqual
		"Error: al ingresar a una sala cambian los espectadores de otra sala"
		3 (espectadoresC c39 1)
	)

testIngresarASala12 = TestCase (
		assertEqual
		"Error: al ingresar a una sala cambian los espectadores de otra sala"
		0 (espectadoresC c39 4)
	)

testIngresarASala13 = TestCase (
		assertEqual
		"Error: al ingresar a una sala cambian los espectadores de otra sala"
		2 (espectadoresC c39 2)
	)

testIngresarASala14 = TestCase (
		assertEqual
		"Error: al ingresar a una sala cambian los espectadores de otra sala"
		0 (espectadoresC c39 3)
	)

testIngresarASala15 = TestCase (
		assertEqual
		"Error: al ingresar a una sala no cambian sus espectadores (cuando deberia sumarse uno)"
		4 (espectadoresC (fst (ingresarASalaC c39 1 t27)) 1)
	)

testIngresarASala16 = TestCase (
		assertEqual
		"Error: al ingresar a una sala no cambian sus espectadores (cuando deberia sumarse uno)"
		0 (espectadoresC (fst (ingresarASalaC c39 2 t31)) 4)
	)

testIngresarASala17 = TestCase (
		assertEqual
		"Error: al ingresar a una sala no cambian sus espectadores (cuando deberia sumarse uno)"
		3 (espectadoresC (fst (ingresarASalaC c39 2 t31)) 2)
	)

testIngresarASala18 = TestCase (
		assertEqual
		"Error: al ingresar a una sala no cambian sus espectadores (cuando deberia sumarse uno)"
		0 (espectadoresC (fst (ingresarASalaC c39 2 t31)) 3)
	)

c40 = snd (pasarA3DUnaPeliculaC c39 "Trompada de Falopio")
c41 = snd (pasarA3DUnaPeliculaC c39 "Sanata para Piano")
c42 = fst (pasarA3DUnaPeliculaC c39 "Trompada de Falopio")
c43 = fst (pasarA3DUnaPeliculaC c39 "Sanata para Piano")

testPasarA3D1 = TestCase (
		assertEqual
		"Error: el nombre de la pelicula pasada a 3D no es el mismo"
		"Trompada de Falopio" (nombreP c40)
	)

testPasarA3D2 = TestCase (
		assertEqual
		"Error: el nombre de la pelicula pasada a 3D no es el mismo"
		"Sanata para Piano" (nombreP c41)
	)

testPasarA3D3 = TestCase (
		assertBool
		"Error: las salas de la pelicula pasada a 3D no son las mismas"
		(mismos (salasC c42) (salasC c39))
	)

testPasarA3D4 = TestCase (
		assertBool
		"Error: las salas de la pelicula pasada a 3D no son las mismas"
		(mismos (salasC c43) (salasC c39))
	)

testPasarA3D5 = TestCase (
		assertBool
		"Error: las salas de la pelicula pasada a 3D no son las mismas"
		(mismos (salasC c43) (salasC c42))
	)

testPasarA3D6 = TestCase (
		assertBool
		"Error: las pelicula no paso a ser 3D!!"
		(es3DP c40)
	)

testPasarA3D7 = TestCase (
		assertBool
		"Error: las pelicula no paso a ser 3D!!"
		(es3DP c41)
	)

testPasarA3D8 = TestCase (
		assertEqual
		"Error: la sala de la pelicula pasada a 3D no sigue siendo la misma"
		4 (salaC c43 ((peliculasC c43)!!0))
	)

testPasarA3D9 = TestCase (
		assertEqual
		"Error: la sala de la pelicula pasada a 3D no sigue siendo la misma"
		4 (salaC c43 ((peliculasC c43)!!0))
	)

testPasarA3D10 = TestCase (
		assertEqual
		"Error: no todos los espectadores son los mismo una vez pasada a 3D la pelicula"
		3 (espectadoresC c42 1)
	)

testPasarA3D11 = TestCase (
		assertEqual
		"Error: no todos los espectadores son los mismo una vez pasada a 3D la pelicula"
		0 (espectadoresC c42 4)
	)


testPasarA3D12 = TestCase (
		assertEqual
		"Error: no todos los espectadores son los mismo una vez pasada a 3D la pelicula"
		2 (espectadoresC c42 2)
	)

c50 = fst (venderTicketC c7 p1)
c51 = fst (venderTicketC (fst (venderTicketC c8 p1)) p2)
c52 = fst (venderTicketC (fst (venderTicketC (fst (venderTicketC (fst (venderTicketC (fst (venderTicketC (fst (venderTicketC c9 p2)) p2)) p1)) p2)) p3)) p2)

testVenderTicket1 = TestCase (
		assertEqual
		"Error: al vender un ticket cambia el nombre del cine"
		"Royal" (nombreC c50)
	)

testVenderTicket2 = TestCase (
		assertEqual
		"Error: al vender un ticket cambia el nombre del cine"
		"Arteplex" (nombreC c51)
	)

c53 = fst (venderTicketC (fst (venderTicketC c8 p1)) p2)

testVenderTicket3 = TestCase (
		assertEqual
		"Error: no esta usando el ticket vendido"
		t2 ((ticketsVendidosC c53)!!0)
	)














--testCerrarSalasDeLaCadenaDejaLosMismosCinesRespetandoLaCota5 = TestCase (
--		assertBool
--		"Error: Cerrar las salas de la cadena no devulve los cines con sus salas correspondiente"
--		([]) (length ([c | c <- [c35, c10, c11, c12], ((nombreC c) == (nombreC c35))]))
--	)

--testCerrarSalasDeLaCadenaDejaLosMismosCinesRespetandoLaCota6 = TestCase (
--		assertBool
--		"Error: Cerrar las salas de la cadena no devulve los cines con sus salas correspondiente"
--		4 (length ([c | c <- [c35, c35, c35, c35], ((nombreC c) == (nombreC c35))]))
--	)





tests = TestList 
				[
					TestLabel "test0" testNombrePelicula1,
					TestLabel "test1" testNombrePelicula2,
					TestLabel "test2" testNombrePelicula3,
					TestLabel "test3" testNombrePelicula4,
					TestLabel "test4" testGenerosPelicula1,
					TestLabel "test5" testGenerosPelicula2,
					TestLabel "test6" testGenerosPelicula3,
					TestLabel "test7" testGenerosPelicula4,
					TestLabel "test8" testActoresPelicula1,
					TestLabel "test9" testActoresPelicula2,
					TestLabel "test10" testActoresPelicula3,
					TestLabel "test11" testActoresPelicula4,
					TestLabel "test12" testEs3DPelicula1,
					TestLabel "test13" testEs3DPelicula2,
					TestLabel "test14" testEs3DPelicula3,
					TestLabel "test15" testEs3DPelicula4,
					TestLabel "test16" testAgruparPelisPorGeneroNoHayGenerosRepetidos1,
					TestLabel "test17" testAgruparPelisPorGeneroNoHayGenerosRepetidos2,
					TestLabel "test18" testAgruparPelisPorGeneroNoHayGenerosRepetidos3,
					TestLabel "test19" testAgruparPelisPorGeneroNoHayGenerosRepetidos4,
					TestLabel "test20" testAgruparPelisPorGeneroNoHayGenerosRepetidos5,
					TestLabel "test21" testAgruparPelisPorGeneroNoHayGenerosRepetidos6,
					TestLabel "test22" testAgruparPelisPorGeneroNoHayGenerosRepetidos7,
					TestLabel "test23" testAgruparPelisPorGeneroNoHayGenerosRepetidos8,
					TestLabel "test24" testAgruparPelisPorGeneroSinCopiasEnGrupos1,
					TestLabel "test25" testAgruparPelisPorGeneroSinCopiasEnGrupos2,
					TestLabel "test26" testAgruparPelisPorGeneroSinCopiasEnGrupos3,
					TestLabel "test27" testAgruparPelisPorGeneroSinCopiasEnGrupos4,
					TestLabel "test28" testAgruparPelisPorGeneroSinCopiasEnGrupos5,
					TestLabel "test29" testAgruparPelisPorGeneroSinCopiasEnGrupos6,
					TestLabel "test30" testAgruparPelisPorGeneroSinCopiasEnGrupos7,
					TestLabel "test31" testAgruparPelisPorGeneroSinCopiasEnGrupos8,
					TestLabel "test32" testAgruparPelisPorGeneroEstanTodasYNoHayDeMas1,
					TestLabel "test33" testAgruparPelisPorGeneroEstanTodasYNoHayDeMas2,
					TestLabel "test34" testAgruparPelisPorGeneroEstanTodasYNoHayDeMas3,
					TestLabel "test35" testAgruparPelisPorGeneroEstanTodasYNoHayDeMas4,
					TestLabel "test36" testAgruparPelisPorGeneroEstanTodasYNoHayDeMas5,
					TestLabel "test37" testAgruparPelisPorGeneroEstanTodasYNoHayDeMas6,
					TestLabel "test38" testGenerarSagaDePeliculasTieneLongitudCorrecta1,
					TestLabel "test39" testGenerarSagaDePeliculasTieneLongitudCorrecta2,
					TestLabel "test40" testGenerarSagaDePeliculasTieneLongitudCorrecta3,
					TestLabel "test41" testGenerarSagaDePeliculasTieneLongitudCorrecta4,
					TestLabel "test42" testGenerarSagaDePeliculasTieneLongitudCorrecta5,
					TestLabel "test43" testGenerarSagaDePeliculasContieneCadaNombredePelicula1,
					TestLabel "test44" testGenerarSagaDePeliculasContieneCadaNombredePelicula2,
					TestLabel "test45" testGenerarSagaDePeliculasContieneCadaNombredePelicula3,
					TestLabel "test46" testPeliculaCorrecta1,
					TestLabel "test47" testPeliculaCorrecta2,
					TestLabel "test48" testPeliculaCorrecta3,
					TestLabel "test49" testSalaCorrecta1,
					TestLabel "test50" testSalaCorrecta2,
					TestLabel "test51" testSalaCorrecta3,
					TestLabel "test52" testUsado1,
					TestLabel "test53" testUsado2,
					TestLabel "test54" testUsado3,
					TestLabel "test55" testUsado4,
					TestLabel "test56" testUsado5,
					TestLabel "test57" testUsado6,
					TestLabel "test58" testUsado7,
					TestLabel "test59" testUsado8,
					TestLabel "test60" testUsado9,
					TestLabel "test61" testPeliculaMenosVistaEsValida1,
					TestLabel "test62" testPeliculaMenosVistaEsValida2,
					TestLabel "test63" testPeliculaMenosVistaEsValida3,
					TestLabel "test64" testPeliculaMenosVistaEsValida4,
					TestLabel "test65" testPeliculaMenosVistaEsValida5,
					TestLabel "test66" testPeliculaMenosVistaEsLaDelTicketMenosUsado1,
					TestLabel "test67" testPeliculaMenosVistaEsLaDelTicketMenosUsado2,
					TestLabel "test68" testPeliculaMenosVistaEsLaDelTicketMenosUsado3,
					TestLabel "test69" testPeliculaMenosVistaEsLaDelTicketMenosUsado4,
					TestLabel "test70" testPeliculaMenosVistaEsLaDelTicketMenosUsado5,
					TestLabel "test71" testPeliculaMenosVistaEsLaDelTicketMenosUsado6,
					TestLabel "test72" testPeliculaMenosVistaEsLaDelTicketMenosUsado7,
					TestLabel "test73" testTodosLosTicketsParaLaMismaSala1,
					TestLabel "test74" testTodosLosTicketsParaLaMismaSala2,
					TestLabel "test75" testTodosLosTicketsParaLaMismaSala3,
					TestLabel "test76" testTodosLosTicketsParaLaMismaSala4,
					TestLabel "test77" testTodosLosTicketsParaLaMismaSala5,
					TestLabel "test78" testTodosLosTicketsParaLaMismaSala6,
					TestLabel "test79" testTodosLosTicketsParaLaMismaSala7,
					TestLabel "test80" testCambiarSalaDejaLaListaConIgualLongitud1,
					TestLabel "test81" testCambiarSalaDejaLaListaConIgualLongitud2,
					TestLabel "test82" testCambiarSalaDejaLaListaConIgualLongitud3,
					TestLabel "test83" testCambiarSalaDejaLaListaConIgualLongitud4,
					TestLabel "test84" testOtrasNoCambian1,
					TestLabel "test85" testOtrasNoCambian2,
					TestLabel "test86" testOtrasNoCambian3,
					TestLabel "test87" testViejaReemplazada1,
					TestLabel "test88" testViejaReemplazada2,
					TestLabel "test89" testViejaReemplazada3,
					TestLabel "test90" testNuevoCineEnOrden1,
					TestLabel "test91" testNuevoCineEnOrden2,
					TestLabel "test92" testNuevoCineEnOrden3,
					TestLabel "test93" testAbrirSalaPreservaElNombre1,
					TestLabel "test94" testAbrirSalaPreservaElNombre2,
					TestLabel "test95" testAbrirSalaPreservaElNombre3,
					TestLabel "test96" testAbrirSalaDejaLasSalasCorresponientes1,
					TestLabel "test97" testAbrirSalaDejaLasSalasCorresponientes2,
					TestLabel "test98" testAbrirSalaPreservaLasPeliculas1,
					TestLabel "test99" testAbrirSalaPreservaLasPeliculas2,
					TestLabel "test100" testAbrirSalaPreservaLasPeliculas3,
					TestLabel "test101" testAbrirSalaPreservaLasPeliculasEnLaSalaEnLaQueEstaban1,
					TestLabel "test102" testAbrirSalaPreservaLasPeliculasEnLaSalaEnLaQueEstaban2,
					TestLabel "test103" testAbrirSalaPreservaLasPeliculasEnLaSalaEnLaQueEstaban3,
					TestLabel "test104" testAbrirSalaPreservaLasPeliculasEnLaSalaEnLaQueEstaban4,
					TestLabel "test105" testAbrirSalaPreservaLasPeliculasEnLaSalaEnLaQueEstaban5,
					TestLabel "test106" testAbrirSalaPreservaLasPeliculasEnLaSalaEnLaQueEstaban6,
					TestLabel "test107" testAbrirSalaPreservaLosEspectadoresOriginales1,
					TestLabel "test108" testAbrirSalaPreservaLosEspectadoresOriginales2,
					TestLabel "test109" testAbrirSalaPreservaLosEspectadoresOriginales3,
					TestLabel "test110" testAbrirSalaPreservaLosEspectadoresOriginales4,
					TestLabel "test111" testAbrirSalaPreservaLosTicketsOriginales1,
					TestLabel "test112" testAbrirSalaPreservaLosTicketsOriginales2,
					TestLabel "test113" testAbrirSalaPreservaLosTicketsOriginales3,
					TestLabel "test114" testAbrirSalaPreservaLosTicketsOriginales4,
					TestLabel "test115" testAgregarPeliculaPreservaElNombre1,
					TestLabel "test116" testAgregarPeliculaPreservaElNombre2,
					TestLabel "test117" testAgregarPeliculaPreservaElNombre3,
					TestLabel "test118" testAgregarPeliculaDejaLasSalasCorresponientes1,
					TestLabel "test119" testAgregarPeliculaDejaLasSalasCorresponientes2,
					TestLabel "test120" testAgregarPeliculaPreservaLosEspectadoresOriginales1,
					TestLabel "test121" testAgregarPeliculaPreservaLosEspectadoresOriginales2,
					TestLabel "test122" testAgregarPeliculaPreservaLosEspectadoresOriginales3,
					TestLabel "test123" testAgregarPeliculaPreservaLosEspectadoresOriginales4,
					TestLabel "test124" testAgregarPeliculaPreservaLosTicketsOriginales,
					TestLabel "test125" testAgregarPeliculaAgregaPeliculaALasPeliculasExistentesDelCine,
					TestLabel "test126" testAgregarPeliculaAgregaLaPeliculaEnLaSalaEspecificada1,
					TestLabel "test127" testAgregarPeliculaAgregaLaPeliculaEnLaSalaEspecificada2,
					TestLabel "test128" testAgregarPeliculaAgregaLaPeliculaEnLaSalaEspecificada3,
					TestLabel "test129" testCerrarSalaPreservaElNombre1,
					TestLabel "test130" testCerrarSalaPreservaElNombre2,
					TestLabel "test131" testCerrarSalaPreservaElNombre3,
					TestLabel "test132" testCerrarSalaSacaLaSalaDelCine1,
					TestLabel "test133" testCerrarSalaSacaLaSalaDelCine2,
					TestLabel "test134" testCerrarSalaSacaLaSalaDelCine3,
					TestLabel "test135" testCerrarSalaMantieneLasPeliculasAExcepcionDeAquellaEnLaSalaCerrada1,
					TestLabel "test136" testCerrarSalaMantieneLasPeliculasAExcepcionDeAquellaEnLaSalaCerrada2,
					TestLabel "test137" testCerrarSalaMantieneLasPeliculasAExcepcionDeAquellaEnLaSalaCerrada3,
					TestLabel "test138" testCerrarSalaMantieneLasPeliculasEnLaMismaSala1,
					TestLabel "test139" testCerrarSalaMantieneLasPeliculasEnLaMismaSala2,
					TestLabel "test140" testCerrarSalaMantieneLasPeliculasEnLaMismaSala3,
					TestLabel "test141" testCerrarSalaMantieneLasPeliculasEnLaMismaSala4,
					TestLabel "test142" testCerrarSalaMantieneLosEspectadoresDeLaSalaOriginal1,
					TestLabel "test143" testCerrarSalaMantieneLosEspectadoresDeLaSalaOriginal2,
					TestLabel "test144" testCerrarSalaMantieneLosEspectadoresDeLaSalaOriginal3,
					TestLabel "test145" testCerrarSalaMantieneLosEspectadoresDeLaSalaOriginal4,
					TestLabel "test146" testCerrarSalaMantieneLosTickets1,
					TestLabel "test147" testCerrarSalaMantieneLosTickets2,
					TestLabel "test148" testCerrarSalaMantieneLosTickets3,
					TestLabel "test149" testCerrarSalasMantieneElNombreDelCine1,
					TestLabel "test150" testCerrarSalasMantieneElNombreDelCine2,
					TestLabel "test151" testCerrarSalasMantieneElNombreDelCine3,
					TestLabel "test152" testCerrarSalasMantieneElNombreDelCine4,
					TestLabel "test153" testCerrarSalasSacaLaSalasCorrespondientesDelCine1,
					TestLabel "test154" testCerrarSalasSacaLaSalasCorrespondientesDelCine2,
					TestLabel "test155" testCerrarSalasSacaLaSalasCorrespondientesDelCine3,
					TestLabel "test156" testCerrarSalasSacaLaSalasCorrespondientesDelCine4,
					TestLabel "test157" testCerrarSalasSacaLaSalasCorrespondientesDelCine5,
					TestLabel "test157" testCerrarSalasSacaLaSalasCorrespondientesDelCine6,
					TestLabel "test158" testCerrarSalasDejaLasPeliculasEnSalasActivasYRemueveLasDeAquellasSalasCerradas1,
					TestLabel "test159" testCerrarSalasDejaLasPeliculasEnSalasActivasYRemueveLasDeAquellasSalasCerradas2,
					TestLabel "test160" testCerrarSalasDejaLasPeliculasEnSalasActivasYRemueveLasDeAquellasSalasCerradas3,
					TestLabel "test161" testCerrarSalasDejaLasPeliculasEnSalasActivasYRemueveLasDeAquellasSalasCerradas4,
					TestLabel "test162" testCerrarSalasDejaLasPeliculasEnSalasActivasYRemueveLasDeAquellasSalasCerradas5,
					TestLabel "test163" testCerrarSalasDejaLasPeliculasEnSalasActivasYRemueveLasDeAquellasSalasCerradas6,
					TestLabel "test164" testCerrarSalasDeLaCadenaDejaLaMismaCantidadDeCines1,
					TestLabel "test165" testCerrarSalasDeLaCadenaDejaLaMismaCantidadDeCines2,
					TestLabel "test166" testCerrarSalasDeLaCadenaDejaLaMismaCantidadDeCines3,
					TestLabel "test167" testCerrarSalasDeLaCadenaDejaLaMismaCantidadDeCines4,
					TestLabel "test168" testCerrarSalasDeLaCadenaDejaLaMismaCantidadDeCines5,
					TestLabel "test169" testCerrarSalasDeLaCadenaDejaLaMismaCantidadDeCines6,
					TestLabel "test170" testCerrarSalasDeLaCadenaDejaLaMismaCantidadDeCines7,
					TestLabel "test171" testCerrarSalasDeLaCadenaDejaLaMismaCantidadDeCines8,
					TestLabel "test172" testCerrarSalasDeLaCadenaDejaLosMismosCinesRespetandoLaCota1,
					TestLabel "test173" testCerrarSalasDeLaCadenaDejaLosMismosCinesRespetandoLaCota2,
					TestLabel "test174" testCerrarSalasDeLaCadenaDejaLosMismosCinesRespetandoLaCota3,
					TestLabel "test175" testCerrarSalasDeLaCadenaDejaLosMismosCinesRespetandoLaCota4,
					TestLabel "test176" testCerrarSalasDeLaCadenaDejaLosMismosCinesRespetandoLaCota5,
					TestLabel "test177" testCerrarSalasDeLaCadenaDejaLosMismosCinesRespetandoLaCota6,
					TestLabel "test178" testCerrarSalasDeLaCadenaDejaLosMismosCinesRespetandoLaCota7,
					TestLabel "test179" testPelicula1,
					TestLabel "test180" testPelicula2,
					TestLabel "test181" testPelicula3,
					TestLabel "test182" testPelicula4,
					TestLabel "test183" testIngresarASala1,
					TestLabel "test184" testIngresarASala2,
					TestLabel "test185" testIngresarASala3,
					TestLabel "test186" testIngresarASala4,
					TestLabel "test187" testIngresarASala5,
					TestLabel "test188" testIngresarASala6,
					TestLabel "test189" testIngresarASala7,
					TestLabel "test190" testIngresarASala8,
					TestLabel "test191" testIngresarASala9,
					TestLabel "test192" testIngresarASala10,
					TestLabel "test193" testIngresarASala11,
					TestLabel "test194" testIngresarASala12,
					TestLabel "test195" testIngresarASala13,
					TestLabel "test196" testIngresarASala14,
					TestLabel "test197" testIngresarASala15,
					TestLabel "test198" testIngresarASala16,
					TestLabel "test199" testIngresarASala17,
					TestLabel "test200" testIngresarASala18,
					TestLabel "test201" testPasarA3D1,
					TestLabel "test202" testPasarA3D2,
					TestLabel "test203" testPasarA3D3,
					TestLabel "test204" testPasarA3D4,
					TestLabel "test205" testPasarA3D5,
					TestLabel "test206" testPasarA3D6,
					TestLabel "test207" testPasarA3D7,
					TestLabel "test208" testPasarA3D8,
					TestLabel "test209" testPasarA3D9,
					TestLabel "test210" testPasarA3D10,
					TestLabel "test211" testPasarA3D11,
					TestLabel "test212" testPasarA3D12,
					TestLabel "test213" testVenderTicket1,
					TestLabel "test214" testVenderTicket2,
					TestLabel "test215" testVenderTicket3









				]



main = do runTestTT tests






















