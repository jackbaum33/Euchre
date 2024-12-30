#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor)
{
    // Ten of clubs
    Card c(TEN, CLUBS);
    ASSERT_EQUAL(TEN, c.get_rank());
    ASSERT_EQUAL(CLUBS, c.get_suit());

    // King of Spades
    Card c2(KING, SPADES);
    ASSERT_EQUAL(KING, c2.get_rank());
    ASSERT_EQUAL(SPADES, c2.get_suit());

     // Six of Diamonds
    Card c1(SIX, DIAMONDS);
    ASSERT_EQUAL(SIX, c1.get_rank());
    ASSERT_EQUAL(DIAMONDS, c1.get_suit());

    // Queen of Hearts
    Card c3(QUEEN, HEARTS);
    ASSERT_EQUAL(QUEEN, c3.get_rank());
    ASSERT_EQUAL(HEARTS, c3.get_suit());
}



TEST(test_suit_comparison)
{
    // if equal cards, suit trumps
    Card ace_spades(ACE, SPADES);
    Card ace_hearts(ACE, HEARTS);
    Card ace_clubs(ACE, CLUBS);
    Card ace_diamonds(ACE, DIAMONDS);
    ASSERT_TRUE(ace_hearts < ace_diamonds);
    // opposite test
    ASSERT_TRUE(ace_diamonds > ace_hearts);
    // spades and hearts
    ASSERT_TRUE(ace_spades < ace_hearts);
    // clubs and diamonds
    ASSERT_TRUE(ace_clubs < ace_diamonds);
    // spades and diamods
    ASSERT_TRUE(ace_diamonds > ace_spades);
}

TEST(Test_get_suit_get_ranks)
{
    Card ace_spades(ACE, SPADES);
    Card king_diamonds(KING, DIAMONDS);
    Card queen_clubs(QUEEN, CLUBS);
    Card jack_hearts(JACK, HEARTS);
    // get_suit
    ASSERT_EQUAL(ace_spades.get_suit(), SPADES);
    ASSERT_EQUAL(king_diamonds.get_suit(), DIAMONDS);
    ASSERT_EQUAL(queen_clubs.get_suit(), CLUBS);
    ASSERT_EQUAL(jack_hearts.get_suit(), HEARTS);

    // get_rank
    ASSERT_EQUAL(ace_spades.get_rank(), ACE);
    ASSERT_EQUAL(king_diamonds.get_rank(), KING);
    ASSERT_EQUAL(queen_clubs.get_rank(), QUEEN);
    ASSERT_EQUAL(jack_hearts.get_rank(), JACK);
}

TEST(Test_is_face_or_ace)
{
    Card ace_spades(ACE, SPADES);
    Card king_diamonds(KING, DIAMONDS);
    Card queen_clubs(QUEEN, CLUBS);
    Card jack_hearts(JACK, HEARTS);
    Card ten_clubs(TEN, CLUBS);

    // Testing all cards
    ASSERT_EQUAL(ace_spades.get_suit(), SPADES);
    ASSERT_EQUAL(ace_spades.get_rank(), ACE);
    ASSERT_EQUAL(king_diamonds.get_suit(), DIAMONDS);
    ASSERT_EQUAL(queen_clubs.get_suit(), CLUBS);
    ASSERT_EQUAL(jack_hearts.get_rank(), JACK);

    ASSERT_TRUE(queen_clubs.is_face_or_ace());
    ASSERT_TRUE(king_diamonds.is_face_or_ace());
    ASSERT_TRUE(jack_hearts.is_face_or_ace());
    ASSERT_TRUE(ace_spades.is_face_or_ace());

    ASSERT_FALSE(ten_clubs.is_face_or_ace());
}

TEST(Test_is_right_bower)
{
    Card jack_spades(JACK, SPADES);
    ASSERT_TRUE(jack_spades.is_right_bower(SPADES));
    // false versions
    ASSERT_FALSE(jack_spades.is_right_bower(CLUBS));
    ASSERT_FALSE(jack_spades.is_right_bower(HEARTS));
    ASSERT_FALSE(jack_spades.is_right_bower(DIAMONDS));
}

TEST(Test_is_left_bower)
{
    Card jack_spades(JACK, SPADES);
    ASSERT_TRUE(jack_spades.is_left_bower(CLUBS));
    // false verisons
    ASSERT_FALSE(jack_spades.is_left_bower(SPADES));
    ASSERT_FALSE(jack_spades.is_left_bower(HEARTS));
    ASSERT_FALSE(jack_spades.is_left_bower(DIAMONDS));
}

TEST(Test_is_trump)
{
    Card jack_spades(JACK, SPADES);
    Card jack_clubs(JACK, CLUBS);
    Card seven_spades(SEVEN, SPADES);
    Card king_spades(KING, SPADES);
    ASSERT_TRUE(jack_spades.is_trump(SPADES));
    ASSERT_TRUE(jack_clubs.is_trump(SPADES));
    ASSERT_TRUE(seven_spades.is_trump(SPADES));
    ASSERT_TRUE(king_spades.is_trump(SPADES));
}

TEST(Test_is_card_less)
{
 Card jack_spades(JACK, SPADES);
    Card jack_clubs(JACK, CLUBS);
    Card jack_hearts(JACK, HEARTS);
    Card jack_diamonds(JACK, DIAMONDS);

    Card ten_hearts(TEN, HEARTS);
    Card ten_diamonds(TEN, DIAMONDS);
    Card ten_clubs(TEN, CLUBS);
    Card ten_spades(TEN, SPADES);
    Card nine_spades(NINE, SPADES);
    Card nine_clubs(NINE, CLUBS);
    Card nine_diamonds(NINE, DIAMONDS);
    Card nine_HEARTS(NINE, HEARTS);

    Card ace_clubs(ACE, CLUBS);
    Card queen_spades(QUEEN, SPADES);
    Card king_spades(KING, SPADES);
    Card ace_hearts(ACE, HEARTS);

    ASSERT_TRUE(Card_less(jack_spades, jack_clubs, CLUBS));
    ASSERT_TRUE(Card_less(ace_clubs, jack_clubs, CLUBS));
    ASSERT_TRUE(Card_less(queen_spades, jack_spades, SPADES));
    ASSERT_TRUE(Card_less(nine_diamonds, jack_diamonds, DIAMONDS));
    ASSERT_FALSE(Card_less(ten_diamonds, ten_clubs, SPADES));
    ASSERT_TRUE(Card_less(ace_hearts, nine_spades, SPADES));

    ASSERT_FALSE(Card_less(ten_diamonds, jack_clubs, DIAMONDS));
    ASSERT_FALSE(Card_less(jack_spades, jack_clubs, SPADES));
    ASSERT_FALSE(Card_less(jack_spades, ace_hearts, SPADES));
}

TEST(Test_is_card_less_lead)
{

    Card jack_spades(JACK, SPADES);
    Card jack_clubs(JACK, CLUBS);
    Card jack_hearts(JACK, HEARTS);
    Card jack_diamonds(JACK, DIAMONDS);

    Card ten_hearts(TEN, HEARTS);
    Card ten_diamonds(TEN, DIAMONDS);
    Card ten_clubs(TEN, CLUBS);
    Card ten_spades(TEN, SPADES);
    Card nine_spades(NINE, SPADES);
    Card nine_clubs(NINE, CLUBS);
    Card nine_diamonds(NINE, DIAMONDS);
    Card nine_hearts(NINE, HEARTS);

    Card ace_clubs(ACE, CLUBS);
    Card queen_spades(QUEEN, SPADES);
    Card king_spades(KING, SPADES);
    Card ace_hearts(ACE, HEARTS);

    ASSERT_TRUE(Card_less(ace_hearts, ace_clubs, ten_clubs, DIAMONDS));
    ASSERT_TRUE(Card_less(nine_clubs, jack_hearts, ten_clubs, DIAMONDS));
    ASSERT_TRUE(Card_less(nine_spades, king_spades, ten_clubs, DIAMONDS));

    ASSERT_TRUE(Card_less(jack_spades, jack_clubs, queen_spades, CLUBS));

    ASSERT_FALSE(Card_less(king_spades, queen_spades, jack_spades, CLUBS));
    ASSERT_TRUE(Card_less(nine_hearts, nine_clubs, queen_spades, CLUBS));
}

TEST(card_equals)
{
    Card ace_spades(ACE,SPADES);
    Card nine_spades(NINE,SPADES);
    ASSERT_FALSE(ace_spades==nine_spades);

    Card jack_clubs(JACK,CLUBS);
    Card jack_diamonds(JACK,DIAMONDS);
    ASSERT_FALSE(jack_clubs==jack_diamonds);
}

TEST(card_get_suit_trump)
{
    Suit trumpSuit(DIAMONDS);
    Card leftBower(JACK,HEARTS);
    ASSERT_EQUAL(leftBower.get_suit(trumpSuit),DIAMONDS);
    Card randomCard(KING,CLUBS);
    ASSERT_EQUAL(randomCard.get_suit(trumpSuit),CLUBS);
}
TEST_MAIN()

