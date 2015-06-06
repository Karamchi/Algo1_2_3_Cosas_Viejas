// g++ -g tests.cpp -o tests
// valgrind --leak-check=full ./tests

#include "mini_test.h"
#include "messineria2.h"

/*
 * Crea una messineria de int vacia y no agrega elementos
 */

void test_interrumpeyvuelve() {
    Messineria<int> messi;
    messi.golDeMessi(1);
    messi.golDeMessi(2);
    messi.golDeMessi(3);
    messi.golDeMessi(4);
    messi.golDeMessi(5);
    messi.golDeMessi(6);
    messi.golDeMessi(7);
    messi.golDeMessi(8);
    messi.golDeMessi(9);
    messi.golDeMessi(10);
    messi.escogerElegido();
    ASSERT_EQ(messi.dameElegido(),1);
    messi.alabarMessi();
    messi.alabarMessi();
    ASSERT_EQ(messi.adeptoAlabando(),3);
    messi.interrumpirTurno();
    ASSERT_EQ(messi.adeptoAlabando(),1);
    messi.alabarMessi();
    ASSERT_EQ(messi.adeptoAlabando(),3);
}

void test_messihermanos(){
    Messineria<int> messi;
    Messineria<int> messi2;
    messi2.golDeMessi(1);
    messi.golDeMessi(1);
    messi.golDeMessi(2);
    messi2.golDeMessi(2);
    messi2.golDeMessi(3);
    messi2.golDeMessi(4);
    messi2.golDeMessi(5);
    messi2.golDeMessi(6);
    messi2.golDeMessi(7);
    messi2.golDeMessi(8);
    messi2.golDeMessi(9);
    messi2.golDeMessi(10);
    messi.golDeMessi(3);
    messi.golDeMessi(4);
    messi.golDeMessi(5);
    messi.golDeMessi(6);
    messi.golDeMessi(7);
    messi.golDeMessi(8);
    messi.golDeMessi(9);
    messi.golDeMessi(10);
    Messineria<int> messi3;
    Messineria<int> messi4;
    messi3.golDeMessi(1);
    ASSERT_EQ(messi3 == messi4, false);
}

void test_unpocodetodo(){
    Messineria<int> messi;

    Messineria<int> messi2;

    ASSERT_EQ(messi2 == messi, true);

    messi2.golDeMessi(1);

    messi.golDeMessi(1);

    ASSERT_EQ(messi2 == messi, true);

    messi.golDeMessi(2);

    messi2.golDeMessi(2);

    ASSERT_EQ(messi2 == messi, true);

    messi2.golDeMessi(3);
    messi2.golDeMessi(4);
    messi2.golDeMessi(5);
    messi2.golDeMessi(6);
    messi2.golDeMessi(7);
    messi2.golDeMessi(8);
    messi2.golDeMessi(9);
    messi2.golDeMessi(10);

    ASSERT_EQ(messi2 == messi, false);

    messi.golDeMessi(3);
    messi.golDeMessi(4);
    messi.golDeMessi(5);

    ASSERT_EQ(messi2 == messi, false);

    messi.golDeMessi(6);
    messi.golDeMessi(7);
    messi.golDeMessi(8);
    messi.golDeMessi(9);
    messi.golDeMessi(10);

    ASSERT_EQ(messi2 == messi, true);

    messi.alabarMessi();
    messi.alabarMessi();
    messi.alabarMessi();
    messi.alabarMessi();
    messi.alabarMessi();
    ASSERT_EQ(messi.adeptoAlabando(),6);

    Messineria<int> messi3(messi);

    //messi.mostrarMessineria(cout);

    //messi3.mostrarMessineria(cout);

    ASSERT_EQ(messi3 == messi, true);

    messi.escogerElegido();
    messi.alabarMessi();
    messi.alabarMessi();
    messi.alabarMessi();
    messi.alabarMessi();
    messi.alabarMessi();
    ASSERT_EQ(messi.dameElegido(),6);
    ASSERT_EQ(messi.hayElegido(),true);
    // messi.mostrarMessineria(cout);

    messi.golDeCristiano(1);
    messi.golDeCristiano(2);
    messi.golDeCristiano(3);
    messi.golDeCristiano(4);
    messi.golDeCristiano(5);
    messi.traidor();
    messi.golDeCristiano(7);
    messi.golDeCristiano(8);
    messi.golDeCristiano(9);
    messi.golDeCristiano(10);


    ASSERT_EQ(messi.esVacia(),true);
}

void test_interrumpeyolvida(){
    Messineria<int> messi;
    messi.golDeMessi(1);
    messi.golDeMessi(2);
    messi.golDeMessi(3);
    messi.golDeMessi(4);
    messi.golDeMessi(5);
    messi.escogerElegido();
    messi.alabarMessi();
    messi.alabarMessi();
    ASSERT_EQ(messi.adeptoAlabando(),3);
    messi.interrumpirTurno();
    ASSERT_EQ(messi.adeptoAlabando(),1);
    messi.olvideAlabarloUnPocoMas();
    ASSERT_EQ(messi.adeptoAlabando(),2);
}

 void test_MessineriaDeMessinerias() {
    Messineria<Messineria<int> > messi;
    Messineria<int> messi2;
    messi2.golDeMessi(1);
    Messineria<int> messi3;
    messi2.golDeMessi(2);
    messi.golDeMessi(messi3);
    messi.golDeMessi(messi2);
    ASSERT_EQ(messi.esVacia(),false);
}

void no_hay_elegido_luego_de_vacia_messineria() {
     Messineria <int> messi1;
     messi1.golDeMessi(3);
     messi1.escogerElegido();
     messi1.golDeCristiano(3);
     ASSERT_EQ(messi1.esVacia(), true);
     ASSERT_EQ(messi1.hayElegido(), false);
}


    void check_metamessi() {
      Messineria< Messineria <int> > messi;

      Messineria <int> messi1;
      messi1.golDeMessi(3);
      messi1.golDeMessi(2);

      Messineria <int> messi2;
      messi2.golDeMessi(5);
      messi2.golDeMessi(4);

      Messineria <int> messi3;
      messi3.golDeMessi(6);
      messi3.golDeMessi(4);

      messi.golDeMessi(messi1);
      ASSERT_EQ(messi.tamanio(), 1);

      messi.golDeMessi(messi2);
      ASSERT_EQ(messi.tamanio(), 2);

      messi.golDeMessi(messi3);
      ASSERT_EQ(messi.tamanio(), 3);

      ASSERT_EQ(messi.hayElegido(), false);

      messi.escogerElegido();

      ASSERT_EQ(messi.hayElegido(), true);
    }




int main() {
    RUN_TEST(test_interrumpeyvuelve);
    RUN_TEST(test_interrumpeyolvida);
    RUN_TEST(test_messihermanos);
    RUN_TEST(test_unpocodetodo);
    RUN_TEST(check_metamessi);
    RUN_TEST(test_MessineriaDeMessinerias);
    RUN_TEST(no_hay_elegido_luego_de_vacia_messineria);
  return 0;
}


