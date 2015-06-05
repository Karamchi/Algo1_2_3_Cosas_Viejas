// g++ -g tests.cpp -o tests
// valgrind --leak-check=full ./tests

#include "mini_test.h"
#include "messineria2.h"

/*
 * Crea una messineria de int vacia y no agrega elementos
 */
void check_crear_messineria_vacia() {
    Messineria<int> messi;
    ASSERT_EQ(messi.esVacia(), true);
    ASSERT_EQ(messi.tamanio(), 0);
}

void check_gol_de_messi_1() {
    Messineria<int> messi;
    messi.golDeMessi(1);
    ASSERT_EQ(messi.esVacia(), false);
    ASSERT_EQ(messi.tamanio(), 1);
}

void check_gol_de_messi_2() {
    Messineria<int> messi;
    messi.golDeMessi(1);
    messi.golDeMessi(2);
    ASSERT_EQ(messi.esVacia(), false);
    ASSERT_EQ(messi.tamanio(), 2);
}

void check_gol_de_messi_3() {
    Messineria<int> messi;
    messi.golDeMessi(1);
    messi.golDeMessi(2);
    messi.golDeMessi(3);
    ASSERT_EQ(messi.esVacia(), false);
    ASSERT_EQ(messi.tamanio(), 3);
    Messineria<int> messi2;
    messi2.golDeMessi(1);
    messi2.golDeMessi(2);
    messi2.golDeMessi(3);
    ASSERT_EQ((messi2==messi), true);
}

void check_const_por_copia() {
    Messineria<int> messi;
    messi.golDeMessi(1);
    messi.golDeMessi(2);
    messi.golDeMessi(3);
    messi.golDeCristiano(2);
    messi.golDeMessi(2);
    messi.alabarMessi();
    messi.alabarMessi();
    messi.escogerElegido();
    messi.traidor();
    messi.golDeMessi(4);
    messi.alabarMessi();
    messi.alabarMessi();
    messi.escogerElegido();
    messi.interrumpirTurno();
    Messineria<int> messi2(messi);
    ASSERT_EQ((messi==messi2), true);
    }


void check_primer_adepto() {
  Messineria<int> messi;
  messi.golDeMessi(1);
  ASSERT_EQ(messi.esVacia(), false);
  ASSERT_EQ(messi.tamanio(), 1);
  ASSERT_EQ(messi.adeptoAlabando(), 1);
  messi.alabarMessi();
  ASSERT_EQ(messi.esVacia(), false);
  ASSERT_EQ(messi.tamanio(), 1);
  ASSERT_EQ(messi.adeptoAlabando(), 1);
  messi.escogerElegido();
  ASSERT_EQ(messi.esVacia(), false);
  ASSERT_EQ(messi.tamanio(), 1);
  ASSERT_EQ(messi.adeptoAlabando(), 1);
  ASSERT_EQ(messi.dameElegido(), 1);
  messi.traidor();
  ASSERT_EQ(messi.esVacia(), true);
  ASSERT_EQ(messi.tamanio(), 0);
}

void check_dos_adeptos() {
  Messineria<int> messi;
  messi.golDeMessi(1);
  messi.golDeMessi(2);
  ASSERT_EQ(messi.esVacia(), false);
  ASSERT_EQ(messi.tamanio(), 2);
  ASSERT_EQ(messi.adeptoAlabando(), 1);
  messi.alabarMessi();
  ASSERT_EQ(messi.adeptoAlabando(), 2);
  messi.escogerElegido();
  ASSERT_EQ(messi.esVacia(), false);
  ASSERT_EQ(messi.tamanio(), 2);
  ASSERT_EQ(messi.adeptoAlabando(), 2);
  ASSERT_EQ(messi.dameElegido(), 2);
  messi.traidor();
  ASSERT_EQ(messi.tamanio(), 1);
  ASSERT_EQ(messi.adeptoAlabando(), 1);
}

void check_ronaldo() {
  Messineria<int> messi;
  messi.golDeMessi(1);
  messi.golDeMessi(2);
  messi.golDeMessi(3);
  messi.alabarMessi();
  messi.alabarMessi();
  messi.golDeCristiano(2);
  ASSERT_EQ(messi.tamanio(), 2);
  ASSERT_EQ(messi.adeptoAlabando(), 3);
}

void check_olvide_alabarlo() {
  Messineria<int> messi;
  messi.golDeMessi(1);
  messi.golDeMessi(2);
  messi.golDeMessi(3);
  messi.alabarMessi();
  messi.alabarMessi();
  messi.olvideAlabarloUnPocoMas();
  ASSERT_EQ(messi.adeptoAlabando(), 2);
  messi.alabarMessi();
  ASSERT_EQ(messi.adeptoAlabando(), 3);
}

void check_interruptus() {
  Messineria<int> messi;
  messi.golDeMessi(1);
  messi.golDeMessi(2);
  messi.golDeMessi(3);
  messi.golDeMessi(4);
  messi.escogerElegido();
  messi.alabarMessi();
  messi.interrumpirTurno();
  ASSERT_EQ(messi.adeptoAlabando(), 1);
  messi.alabarMessi();
  ASSERT_EQ(messi.adeptoAlabando(), 2);
  messi.alabarMessi();
  messi.alabarMessi();
  messi.alabarMessi();
  ASSERT_EQ(messi.adeptoAlabando(), 1);
}

void check_copia(){
  Messineria<int> messi;
  Messineria<int> messi2(messi);
}

 void check_MessineriaDeMessinerias() {
    Messineria<Messineria<int> > messi;
    Messineria<int> messi2;
    messi2.golDeMessi(1);
    Messineria<int> messi3;
    messi2.golDeMessi(2);
    messi.golDeMessi(messi3);
    messi.golDeMessi(messi2);
    ASSERT_EQ(messi.esVacia(),false);
}


int main() {
  RUN_TEST(check_crear_messineria_vacia);
  RUN_TEST(check_gol_de_messi_1);
  RUN_TEST(check_gol_de_messi_2);
  RUN_TEST(check_gol_de_messi_3);
  RUN_TEST(check_primer_adepto);
  RUN_TEST(check_dos_adeptos);
  RUN_TEST(check_ronaldo);
  RUN_TEST(check_olvide_alabarlo);
  RUN_TEST(check_interruptus);
  RUN_TEST(check_copia);
  RUN_TEST(check_const_por_copia);
  RUN_TEST(check_MessineriaDeMessinerias);
  return 0;
}

