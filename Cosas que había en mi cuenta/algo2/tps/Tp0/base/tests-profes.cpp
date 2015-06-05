// g++ -g tests.cpp -o tests
// valgrind --leak-check=full -v ./tests

#include "mini_test.h"
#include "messineria2.h"

 
template<typename T>
string to_s(const T& m) {
 	ostringstream os;
	os << m;
	return os.str();
 }
 

/*
 * Crea una messineria de int vacia y no agrega elementos
 */
void check_crear_messineria_vacia() {
  Messineria<int> messi;

  ASSERT_EQ(messi.esVacia(), true);

  ASSERT_EQ(messi.tamanio(), 0);
}

/*
 * Agrega 3 elementos y verifica que esten agregados segun lo pedido
 */
void check_agregar_adeptos() {
  Messineria<int> messi;
  messi.golDeMessi(2);
  messi.golDeMessi(7);
  messi.golDeMessi(3);

  ASSERT(!messi.esVacia());

  ASSERT_EQ(to_s(messi), "[2, 7, 3]");
 
  ASSERT_EQ(messi.tamanio(), 3);
}

/*
 * Agrega elementos y verifica que esten ASSERT(messi == messi2);agregados a la izquierda del elegido
 */
void check_agregar_adeptos_con_elegido() {
  Messineria<int> messi;
  messi.golDeMessi(2);
  messi.golDeMessi(7);
  messi.escogerElegido();
  ASSERT_EQ(messi.dameElegido(), messi.adeptoAlabando());
  ASSERT_EQ(to_s(messi), "[2*, 7]");
  messi.golDeMessi(10);
  ASSERT_EQ(to_s(messi), "[2*, 7, 10]");
  messi.golDeMessi(8);
  ASSERT_EQ(to_s(messi), "[2*, 7, 10, 8]");
  messi.alabarMessi();
  ASSERT_EQ(to_s(messi), "[7, 10, 8, 2*]");
  messi.golDeMessi(5);
  ASSERT_EQ(to_s(messi), "[7, 10, 8, 5, 2*]");
}


/*
 * Se copia una messineria y verifica que sus atributos sean iguales.
 * Si hay Elegido se debería copiar el Elegido.
 * Si hay interrupción se debería volver al mismo luego de alabar
 */
void check_copiar_sin_elegido() {
  Messineria<int> messi;
  messi.golDeMessi(2);
  messi.golDeMessi(7);
  messi.golDeMessi(10);
  ASSERT_EQ(to_s(messi), "[2, 7, 10]");
  Messineria<int> messi2(messi);
  ASSERT(messi == messi2);
}

void check_copiar_con_elegido() {
  Messineria<int> messi;
  messi.golDeMessi(2);
  messi.golDeMessi(7);
  messi.golDeMessi(10);
  messi.escogerElegido();
  ASSERT_EQ(to_s(messi), "[2*, 7, 10]");
  Messineria<int> messi2(messi);
  ASSERT(messi == messi2);
  messi.interrumpirTurno();
  messi2.interrumpirTurno();
  ASSERT(messi == messi2);
}

/*
 * Quita elementos despues de agregar
 */
void check_quitar_adeptos() {
  Messineria<int> messi;
  messi.golDeMessi(2);
  messi.golDeMessi(7);
  messi.golDeMessi(3);
  messi.golDeMessi(4);
  messi.golDeMessi(5);

  messi.golDeCristiano(3);
 
  ASSERT_EQ(to_s(messi), "[2, 7, 4, 5]");
  
  messi.golDeCristiano(7);
 
  ASSERT_EQ(to_s(messi), "[2, 4, 5]");

  messi.golDeCristiano(2);
  
  ASSERT_EQ(to_s(messi), "[4, 5]");
  ASSERT_EQ(messi.tamanio(), 2);
}

/*
 * Verifica que el que esta alabando sea el correcto sin llamar a alabar.
 * Solo agrega y quita elementos
 */
void check_alabador() {
  Messineria<int> messi;
  messi.golDeMessi(2);
  
  ASSERT_EQ(messi.adeptoAlabando(), 2)
  
  messi.golDeMessi(7);
  
  ASSERT_EQ(messi.adeptoAlabando(), 2)
    
  messi.golDeMessi(3);
  messi.golDeMessi(4);
  messi.golDeMessi(5);
  messi.golDeCristiano(3); 
  messi.golDeCristiano(7);
  messi.golDeCristiano(2);
  messi.golDeMessi(7);

  ostringstream oss;
  oss << messi.adeptoAlabando();
  ASSERT_EQ(oss.str(), "4")

  messi.golDeCristiano(4);

  oss.str("");
  oss << messi.adeptoAlabando();
  ASSERT_EQ(oss.str(), "5");
}

/*
 * Verifica que el que esta alabando sea el correcto llamando a alabar
 */
void check_alabar() {
  Messineria<int> messi;
  messi.golDeMessi(2);
  messi.golDeMessi(7);
  messi.golDeMessi(3);
  messi.golDeMessi(4);
  messi.golDeMessi(5);
  messi.golDeCristiano(3); 
  messi.golDeCristiano(7);
  messi.golDeCristiano(2);
  messi.golDeMessi(7);
  
  ASSERT_EQ(to_s(messi.alabarMessi()), "5");
  ASSERT_EQ(to_s(messi.alabarMessi()), "7");
  ASSERT_EQ(to_s(messi), "[7, 4, 5]");
  ASSERT_EQ(to_s(messi.alabarMessi()), "4");
  ASSERT_EQ(to_s(messi.alabarMessi()), "5");
  ASSERT_EQ(to_s(messi), "[5, 7, 4]");
}

/*
 * Chequea varias llamadas de olvideAlabarloUnPocoMas y alabar
 */
void check_olvide() {
  Messineria<int> messi;
  messi.golDeMessi(2);
  messi.golDeMessi(7);
  messi.golDeMessi(3);
  messi.golDeMessi(4);
  messi.golDeMessi(5);
  messi.golDeCristiano(3); 
  messi.golDeCristiano(7);
  messi.golDeCristiano(2);
  messi.golDeMessi(7);
  
  ASSERT_EQ(to_s(messi.alabarMessi()), "5");
  messi.olvideAlabarloUnPocoMas();
  ASSERT_EQ(to_s(messi), "[4, 5, 7]");
  messi.olvideAlabarloUnPocoMas();
  ASSERT_EQ(to_s(messi), "[7, 4, 5]");
  messi.golDeMessi(3);
  ASSERT_EQ(to_s(messi.adeptoAlabando()),"7");
  ASSERT_EQ(to_s(messi.alabarMessi()), "4");
  ASSERT_EQ(to_s(messi), "[4, 5, 3, 7]");
  messi.olvideAlabarloUnPocoMas();
  ASSERT_EQ(to_s(messi), "[7, 4, 5, 3]");
}

/*
 * Verifica que las interrupciones del Elegido sean atendidas
 */
void check_interrumpir() {
  Messineria<int> messi;
  messi.golDeMessi(2);
  messi.golDeMessi(7);
  messi.golDeMessi(3);
  messi.golDeMessi(4);
  messi.golDeMessi(5);
  messi.golDeCristiano(3); 
  messi.golDeCristiano(7);
  messi.golDeCristiano(2);
  messi.golDeMessi(7);
  
  ASSERT_EQ(to_s(messi.alabarMessi()), "5");
  messi.olvideAlabarloUnPocoMas();
  ASSERT_EQ(to_s(messi), "[4, 5, 7]");
  messi.olvideAlabarloUnPocoMas();
  ASSERT_EQ(to_s(messi), "[7, 4, 5]");
  messi.golDeMessi(3);
  ASSERT_EQ(to_s(messi.adeptoAlabando()),"7");
  ASSERT_EQ(to_s(messi.alabarMessi()), "4");
  ASSERT_EQ(to_s(messi), "[4, 5, 3, 7]");
  messi.olvideAlabarloUnPocoMas();
  ASSERT_EQ(to_s(messi), "[7, 4, 5, 3]");

  messi.escogerElegido();
  messi.alabarMessi();
  messi.alabarMessi();
  messi.interrumpirTurno();
  ASSERT_EQ(to_s(messi.adeptoAlabando()),"7");
  messi.alabarMessi();
  ASSERT_EQ(to_s(messi), "[5, 3, 7*, 4]");
}

/*
 * Verifica varias combinaciones de escogerElegido, alabar, olvideAlabar,
 * traidor
 */

void check_elegido() {
  Messineria<int> messi;
  messi.golDeMessi(2);
  messi.golDeMessi(7);
  messi.golDeMessi(3);
  messi.golDeMessi(4);
  messi.golDeMessi(5);
  messi.golDeCristiano(3); 
  messi.golDeCristiano(7);
  messi.golDeCristiano(2);
  messi.golDeMessi(7);
  messi.alabarMessi();
  messi.olvideAlabarloUnPocoMas();
  messi.olvideAlabarloUnPocoMas();
  messi.golDeMessi(3);
  messi.adeptoAlabando();
  messi.alabarMessi();
  messi.olvideAlabarloUnPocoMas();
  ASSERT_EQ(to_s(messi), "[7, 4, 5, 3]");

  messi.escogerElegido();
  ASSERT_EQ(to_s(messi), "[7*, 4, 5, 3]");

  messi.alabarMessi();
  ASSERT_EQ(to_s(messi), "[4, 5, 3, 7*]");

  messi.alabarMessi();
  messi.golDeCristiano(3);
  messi.golDeMessi(8);

  ASSERT_EQ(to_s(messi), "[5, 8, 7*, 4]");
  ASSERT_EQ(to_s(messi.dameElegido()), "7");
  ASSERT(messi.hayElegido());
  messi.golDeCristiano(7);
  ASSERT_EQ(to_s(messi), "[5, 8, 4]");
  ASSERT_EQ(messi.tamanio(), 3);
  messi.escogerElegido();
  ASSERT_EQ(to_s(messi.dameElegido()), "5");
  messi.golDeCristiano(5);
  ASSERT(!messi.hayElegido());
  ASSERT_EQ(to_s(messi), "[8, 4]");

  messi.escogerElegido();
  ASSERT_EQ(to_s(messi.dameElegido()), "8");
  messi.traidor();
  ASSERT_EQ(to_s(messi), "[4]");

}

/*
 * Se crean varias Messinerias que se modifican pero deberían ser igua-
 * les
 */
void check_igualdad() {
  Messineria<int> messi;
  messi.golDeMessi(2);
  messi.golDeMessi(7);
  messi.golDeMessi(3);
  messi.golDeMessi(4);
  messi.golDeMessi(5);
  messi.golDeCristiano(3); 
  messi.golDeCristiano(7);
  messi.golDeCristiano(2);
  messi.golDeMessi(7);
  messi.alabarMessi();
  messi.olvideAlabarloUnPocoMas();
  messi.olvideAlabarloUnPocoMas();
  messi.golDeMessi(3);
  messi.adeptoAlabando();
  messi.alabarMessi();
  messi.olvideAlabarloUnPocoMas();
  messi.escogerElegido();
  messi.alabarMessi();
  messi.alabarMessi();
  messi.golDeCristiano(3);
  messi.golDeMessi(8);
  messi.golDeCristiano(7);
  messi.escogerElegido();
  messi.golDeCristiano(5);
  ASSERT_EQ(to_s(messi), "[8, 4]");

  Messineria<int> messi3;
  ASSERT(not(messi == messi3));

  messi.golDeMessi(5);
  messi.golDeMessi(7);
  messi.escogerElegido();
  messi.golDeMessi(9);
  ASSERT_EQ(to_s(messi), "[8*, 4, 5, 7, 9]");

  Messineria<int> messi2(messi);
  messi2.olvideAlabarloUnPocoMas();
  messi2.alabarMessi();
  messi2.alabarMessi();
  messi.olvideAlabarloUnPocoMas();
  messi.alabarMessi();
  messi.alabarMessi();

  ostringstream os;
  os << messi;

  ASSERT_EQ(to_s(messi2), os.str());
  ASSERT(messi==messi2);
  messi.alabarMessi();
  ASSERT(not(messi == messi3));
}

/*
 * Instancia una Messineria<Messineria<int> >
 * Útils para chequear errores en el constructor por copia y la igualdad
 */
void check_messineria_messineria() {

  Messineria<int> messi1;
  messi1.golDeMessi(2);
  messi1.golDeMessi(7);
  messi1.golDeMessi(3);
   
  Messineria<int> messi2;
  messi2.golDeMessi(40);
  messi2.golDeMessi(50);
  messi2.golDeMessi(60);
  
  Messineria<Messineria<int> > messi_messi;
  
  messi_messi.golDeMessi(messi1);
  messi_messi.golDeMessi(messi2);
}


int main() {
  RUN_TEST(check_crear_messineria_vacia);
  RUN_TEST(check_agregar_adeptos);
  RUN_TEST(check_quitar_adeptos);
  RUN_TEST(check_alabador);
  RUN_TEST(check_alabar);
  RUN_TEST(check_olvide);
  RUN_TEST(check_elegido);
  RUN_TEST(check_interrumpir);
  RUN_TEST(check_igualdad);
  RUN_TEST(check_messineria_messineria);
  RUN_TEST(check_agregar_adeptos_con_elegido);
  RUN_TEST(check_copiar_sin_elegido);  
  RUN_TEST(check_copiar_con_elegido);

  return 0;
}

