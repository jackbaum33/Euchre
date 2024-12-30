#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name_basic) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
    Player *Smith = Player_factory("Smith", "Human");
    ASSERT_EQUAL(Smith->get_name(),"Smith");
    delete Smith;
}

TEST(player_get_name_blank)
{
    Player* blankName=Player_factory("","Simple");
    ASSERT_EQUAL(blankName->get_name(),"");
    delete blankName;

    Player* blankHuman=Player_factory("","Human");
    ASSERT_EQUAL(blankHuman->get_name(),"");
    delete blankHuman;
}

TEST(make_trump_round_one)
{
    Player* jack=Player_factory("jack","Simple");
    Card cardOne(NINE,CLUBS);
    Card cardTwo(TEN,CLUBS);
    Card cardThree(NINE,SPADES);
    Card cardFour(TEN,HEARTS);
    Card cardFive(JACK,CLUBS);
    Card upcard(KING,CLUBS);
    jack->add_card(cardOne);
    jack->add_card(cardTwo);
    jack->add_card(cardThree);
    jack->add_card(cardFour);
    jack->add_card(cardFive);

    int round =1;
    bool isDealer=false;
    Suit orderUpSuit(DIAMONDS);
    ASSERT_FALSE(jack->make_trump(upcard,isDealer,round,orderUpSuit));
    ASSERT_EQUAL(orderUpSuit,DIAMONDS);
    delete jack;

}
TEST(no_screw_round_one)
{
    Player* jack=Player_factory("jack","Simple");
    Card cardOne(NINE,CLUBS);
    Card cardTwo(TEN,CLUBS);
    Card cardThree(NINE,SPADES);
    Card cardFour(TEN,HEARTS);
    Card cardFive(JACK,CLUBS);
    Card upcard(KING,CLUBS);
    jack->add_card(cardOne);
    jack->add_card(cardTwo);
    jack->add_card(cardThree);
    jack->add_card(cardFour);
    jack->add_card(cardFive);
    int round =1;
    bool isDealer=true;
    Suit orderUpSuit(DIAMONDS);
    ASSERT_FALSE(jack->make_trump(upcard,isDealer,round,orderUpSuit));
    ASSERT_EQUAL(orderUpSuit,DIAMONDS);
    delete jack;
}
TEST(make_trump_round_one_true)
{

    Player *eli=Player_factory("eli","Simple");
    Card cardEliOne(QUEEN,CLUBS);
    Card cardEliTwo(TEN,CLUBS);
    Card cardEliThree(NINE,SPADES);
    Card cardEliFour(TEN,DIAMONDS);
    Card cardEliFive(JACK,CLUBS);
    Card eliUpcard(KING,CLUBS);
    eli->add_card(cardEliOne);
    eli->add_card(cardEliTwo);
    eli->add_card(cardEliThree);
    eli->add_card(cardEliFour);
    eli->add_card(cardEliFive);
    int roundEli =1;
    bool isDealerEli=false;
    Suit orderUpSuitEli(HEARTS);
    ASSERT_TRUE(eli->make_trump(eliUpcard,isDealerEli,roundEli,orderUpSuitEli));
    ASSERT_EQUAL(orderUpSuitEli,CLUBS);
    delete eli;
}
TEST(make_trump_two_true)
{
    Player* josh=Player_factory("josh","Simple");
    Card cardTen(JACK,CLUBS);
    Card cardSix(KING,SPADES);
    Card cardSeven(QUEEN,SPADES);
    Card cardEight(ACE,DIAMONDS);
    Card cardNine(JACK,CLUBS);
    Card upcardTwo(KING,CLUBS);
    josh->add_card(cardSix);
    josh->add_card(cardSeven);
    josh->add_card(cardEight);
    josh->add_card(cardNine);
    josh->add_card(cardTen);
    int roundTwo =2;
    bool isDealerTwo=false;
    Suit orderUpSuitTwo(DIAMONDS);
    ASSERT_TRUE(josh->make_trump(upcardTwo,isDealerTwo,roundTwo,orderUpSuitTwo));
    ASSERT_EQUAL(orderUpSuitTwo,SPADES);
    delete josh;
}

TEST(round_two_trump_doesnt)
{
    Player* chinny=Player_factory("chinny","Simple");
    Card cardTenChinny(TEN,CLUBS);
    Card cardSixChinny(NINE,SPADES);
    Card cardSevenChinny(TEN,SPADES);
    Card cardEightChinny(NINE,DIAMONDS);
    Card cardNineChinny(QUEEN,HEARTS);

    Card upcardTwoChinny(KING,CLUBS);
    chinny->add_card(cardSixChinny);
    chinny->add_card(cardSevenChinny);
    chinny->add_card(cardEightChinny);
    chinny->add_card(cardNineChinny);
    chinny->add_card(cardTenChinny);
    int roundTwoChinny =2;
    bool isDealerTwoChinny=false;
    Suit orderUpSuitTwoChinny(DIAMONDS);
    ASSERT_FALSE(chinny->make_trump(upcardTwoChinny,
    isDealerTwoChinny,roundTwoChinny,orderUpSuitTwoChinny));
    ASSERT_EQUAL(orderUpSuitTwoChinny,DIAMONDS);
    delete chinny;
}


TEST(make_trump_one_card_left_bower)
{
    Player* levi=Player_factory("levi","Simple");
    Card cardTenLevi(JACK,SPADES);
    Card cardSixLevi(TEN,SPADES);
    Card cardSevenLevi(NINE,SPADES);
    Card cardEightLevi(NINE,DIAMONDS);
    Card cardNineLevi(JACK,CLUBS);

    Card upcardTwoLevi(KING,CLUBS);
    levi->add_card(cardSixLevi);
    levi->add_card(cardSevenLevi);
    levi->add_card(cardEightLevi);
    levi->add_card(cardNineLevi);
    levi->add_card(cardTenLevi);
    int roundLevi =1;
    bool isDealerLevi=false;
    Suit orderUpSuitLevi(DIAMONDS);
    ASSERT_TRUE(levi->make_trump(upcardTwoLevi,isDealerLevi,roundLevi,orderUpSuitLevi));
    ASSERT_EQUAL(orderUpSuitLevi,CLUBS);
    delete levi;

}

TEST(test_screw_the_dealer)
{
    Player* michael=Player_factory("michael","Simple");
    Card cardOneMichael(NINE,CLUBS);
    Card cardTwoMichael(TEN,SPADES);
    Card cardThreeMichael(NINE,SPADES);
    Card cardFourMichael(NINE,DIAMONDS);
    Card cardFiveMichael(TEN,HEARTS);

    Card upcardMichael(KING,CLUBS);
    michael->add_card(cardOneMichael);
    michael->add_card(cardTwoMichael);
    michael->add_card(cardThreeMichael);
    michael->add_card(cardFourMichael);
    michael->add_card(cardFiveMichael);
    int roundMichael =2;
    bool isDealerMichael=true;
    Suit orderUpSuitMichael(DIAMONDS);
    ASSERT_TRUE(michael->make_trump(upcardMichael,isDealerMichael,roundMichael,orderUpSuitMichael));
    ASSERT_EQUAL(orderUpSuitMichael,SPADES);
    delete michael;
}

TEST (add_and_discard_keeps_upcard)
{
    Player* michael=Player_factory("michael","Simple");
    Card cardOneMichael(NINE,HEARTS);
    Card cardTwoMichael(TEN,DIAMONDS);
    Card cardThreeMichael(QUEEN,HEARTS);
    Card cardFourMichael(ACE,HEARTS);
    Card cardFiveMichael(TEN,HEARTS);
    Card leadCardMichael(KING,CLUBS);
    michael->add_card(cardOneMichael);
    michael->add_card(cardTwoMichael);
    michael->add_card(cardThreeMichael);
    michael->add_card(cardFourMichael);
    michael->add_card(cardFiveMichael);
    ASSERT_EQUAL(michael->play_card(leadCardMichael,leadCardMichael.get_suit()),cardOneMichael);
    michael->add_card(cardOneMichael);
    Card upcardMichael(QUEEN,SPADES);
    michael->add_and_discard(upcardMichael);
    ASSERT_EQUAL(michael->play_card(leadCardMichael,leadCardMichael.get_suit()),cardFiveMichael);
    delete michael;
}

TEST(add_and_discard_discards_upcard)
{
    Player* michael=Player_factory("michael","Simple");
    Card cardOneMichael(JACK,HEARTS);
    Card cardTwoMichael(TEN,HEARTS);
    Card cardThreeMichael(QUEEN,HEARTS);
    Card cardFourMichael(ACE,HEARTS);
    Card cardFiveMichael(KING,HEARTS);
    Card leadCardMichael(KING,CLUBS);
    michael->add_card(cardOneMichael);
    michael->add_card(cardTwoMichael);
    michael->add_card(cardThreeMichael);
    michael->add_card(cardFourMichael);
    michael->add_card(cardFiveMichael);
    ASSERT_EQUAL(michael->play_card(leadCardMichael,leadCardMichael.get_suit()),cardTwoMichael);
     michael->add_card(cardTwoMichael);
     Card upcardMichael(NINE,HEARTS);
     michael->add_and_discard(upcardMichael);
   ASSERT_EQUAL(michael->play_card(leadCardMichael,leadCardMichael.get_suit()),cardTwoMichael);
   delete michael;
}

TEST(lead_right_bower_over_left)
{
    Player* plotkin=Player_factory("plotkin","Simple");
    Card cardOnePlotkin(JACK,CLUBS);
    Card cardTwoPlotkin(KING,SPADES);
    Card cardThreePlotkin(ACE,SPADES);
    Card cardFourPlotkin(QUEEN,SPADES);
    Card cardFivePlotkin(JACK,SPADES);
    plotkin->add_card(cardOnePlotkin);
    plotkin->add_card(cardTwoPlotkin);
    plotkin->add_card(cardThreePlotkin);
    plotkin->add_card(cardFourPlotkin);
    plotkin->add_card(cardFivePlotkin);
    Suit trumpSuit(SPADES);
    ASSERT_EQUAL(plotkin->lead_card(trumpSuit),cardFivePlotkin);
    delete plotkin;
    }    


TEST(doesnt_consider_left_bower_as_non_trump)
{
Player* plotkin=Player_factory("plotkin","Simple");
    Card cardOnePlotkin(JACK,CLUBS);
    Card cardTwoPlotkin(KING,DIAMONDS);
    Card cardThreePlotkin(ACE,SPADES);
    Card cardFourPlotkin(QUEEN,SPADES);
    Card cardFivePlotkin(JACK,SPADES);
    plotkin->add_card(cardOnePlotkin);
    plotkin->add_card(cardTwoPlotkin);
    plotkin->add_card(cardThreePlotkin);
    plotkin->add_card(cardFourPlotkin);
    plotkin->add_card(cardFivePlotkin);
    Suit trumpSuit(SPADES);
    ASSERT_EQUAL(plotkin->lead_card(trumpSuit),cardTwoPlotkin);
    delete plotkin;
}
TEST(simple_lead_card)
{
    Player* johnson = Player_factory("johnson","Simple");
    Card cardOneJohnson(TEN,HEARTS);
    Card cardTwoJohnson(KING,CLUBS);
    Card cardThreeJohnson(ACE,CLUBS);
    Card cardFourJohnson(QUEEN,CLUBS);
    Card cardFiveJohnson(JACK,CLUBS);
    johnson->add_card(cardOneJohnson);
    johnson->add_card(cardTwoJohnson);
    johnson->add_card(cardThreeJohnson);
    johnson->add_card(cardFourJohnson);
    johnson->add_card(cardFiveJohnson);
    Suit trumpSuitJohnson(CLUBS);
    ASSERT_EQUAL(johnson->lead_card(trumpSuitJohnson),cardOneJohnson);
    delete johnson;
}
TEST(lead_all_trump){
    Player* schnitzel=Player_factory("schnitzel","Simple");
    Card cardOneSchnitzel(TEN,CLUBS);
    Card cardTwoSchnitzel(KING,CLUBS);
    Card cardThreeSchnitzel(ACE,CLUBS);
    Card cardFourSchnitzel(QUEEN,CLUBS);
    Card cardFiveSchnitzel(NINE,CLUBS);
    schnitzel->add_card(cardOneSchnitzel);
    schnitzel->add_card(cardTwoSchnitzel);
    schnitzel->add_card(cardThreeSchnitzel);
    schnitzel->add_card(cardFourSchnitzel);
    schnitzel->add_card(cardFiveSchnitzel);
    Suit trumpSuitSchnitzel(CLUBS);
    ASSERT_EQUAL(schnitzel->lead_card(trumpSuitSchnitzel).get_rank(),ACE);
    ASSERT_EQUAL(schnitzel->lead_card(trumpSuitSchnitzel).get_suit(),CLUBS);
    delete schnitzel;
}

TEST(highest_value_left_bower)
{
    Player* schnitzel=Player_factory("schnitzel","Simple");
    Card cardOneSchnitzel(TEN,HEARTS);
    Card cardTwoSchnitzel(KING,HEARTS);
    Card cardThreeSchnitzel(ACE,HEARTS);
    Card cardFourSchnitzel(QUEEN,HEARTS);
    Card cardFiveSchnitzel(JACK,CLUBS);
    schnitzel->add_card(cardOneSchnitzel);
    schnitzel->add_card(cardTwoSchnitzel);
    schnitzel->add_card(cardThreeSchnitzel);
    schnitzel->add_card(cardFourSchnitzel);
    schnitzel->add_card(cardFiveSchnitzel);
    Suit trumpSuitSchnitzel(SPADES);
    ASSERT_EQUAL(schnitzel->lead_card(trumpSuitSchnitzel).get_rank(),ACE);
    ASSERT_EQUAL(schnitzel->lead_card(trumpSuitSchnitzel).get_suit(),HEARTS);
    delete schnitzel;

}
TEST(play_card_left_bower_highest)
{
   Player* plotkin=Player_factory("plotkin","Simple");
    Card cardOnePlotkin(TEN,HEARTS);
    Card cardTwoPlotkin(KING,HEARTS);
    Card cardThreePlotkin(ACE,HEARTS);
    Card cardFourPlotkin(QUEEN,HEARTS);
    Card cardFivePlotkin(JACK,CLUBS);
    plotkin->add_card(cardOnePlotkin);
    plotkin->add_card(cardTwoPlotkin);
    plotkin->add_card(cardThreePlotkin);
    plotkin->add_card(cardFourPlotkin);
    plotkin->add_card(cardFivePlotkin);
    Suit trumpSuitPlotkin(SPADES);
    Card led_card(NINE,SPADES);
    ASSERT_EQUAL(plotkin->play_card(led_card,trumpSuitPlotkin).get_rank(),JACK);
    plotkin->add_card(cardFivePlotkin);
    ASSERT_EQUAL(plotkin->play_card(led_card,trumpSuitPlotkin).get_suit(trumpSuitPlotkin),SPADES);
    delete plotkin;

}

TEST(play_card_right_bower_highest)
{
   Player* plotkin=Player_factory("plotkin","Simple");
    Card cardOnePlotkin(TEN,HEARTS);
    Card cardTwoPlotkin(KING,HEARTS);
    Card cardThreePlotkin(ACE,HEARTS);
    Card cardFourPlotkin(QUEEN,HEARTS);
    Card cardFivePlotkin(JACK,SPADES);
    plotkin->add_card(cardOnePlotkin);
    plotkin->add_card(cardTwoPlotkin);
    plotkin->add_card(cardThreePlotkin);
    plotkin->add_card(cardFourPlotkin);
    plotkin->add_card(cardFivePlotkin);
    Suit trumpSuitPlotkin(SPADES);
    Card led_card(NINE,SPADES);
    ASSERT_EQUAL(plotkin->play_card(led_card,trumpSuitPlotkin).get_rank(),JACK);
    plotkin->add_card(cardFivePlotkin);
    ASSERT_EQUAL(plotkin->play_card(led_card,trumpSuitPlotkin).get_suit(trumpSuitPlotkin),SPADES);
    delete plotkin;

}
TEST(play_right_bower_over_left)
{
    Player* plotkin=Player_factory("plotkin","Simple");
    Card cardOnePlotkin(JACK,CLUBS);
    Card cardTwoPlotkin(KING,HEARTS);
    Card cardThreePlotkin(ACE,HEARTS);
    Card cardFourPlotkin(QUEEN,HEARTS);
    Card cardFivePlotkin(JACK,SPADES);
    plotkin->add_card(cardOnePlotkin);
    plotkin->add_card(cardTwoPlotkin);
    plotkin->add_card(cardThreePlotkin);
    plotkin->add_card(cardFourPlotkin);
    plotkin->add_card(cardFivePlotkin);
    Suit trumpSuitPlotkin(SPADES);
    Card led_card(NINE,SPADES);
    ASSERT_EQUAL(plotkin->play_card(led_card,trumpSuitPlotkin),cardFivePlotkin);
    delete plotkin;
}
TEST(play_card_no_lead){
    Player* plotkin=Player_factory("plotkin","Simple");
    Card cardOnePlotkin(TEN,CLUBS);
    Card cardTwoPlotkin(KING,CLUBS);
    Card cardThreePlotkin(ACE,CLUBS);
    Card cardFourPlotkin(QUEEN,CLUBS);
    Card cardFivePlotkin(JACK,CLUBS);
    plotkin->add_card(cardOnePlotkin);
    plotkin->add_card(cardTwoPlotkin);
    plotkin->add_card(cardThreePlotkin);
    plotkin->add_card(cardFourPlotkin);
    plotkin->add_card(cardFivePlotkin);
    Card leadCardPlotkin(NINE,SPADES);
    ASSERT_EQUAL(plotkin->play_card(leadCardPlotkin,DIAMONDS),cardOnePlotkin);
    delete plotkin;
}

TEST(simple_play_card)
{
    Player* emily=Player_factory("emily","Simple");
    Card cardOneEmily(TEN,CLUBS);
    Card cardTwoEmily(KING,CLUBS);
    Card cardThreeEmily(ACE,CLUBS);
    Card cardFourEmily(QUEEN,CLUBS);
    Card cardFiveEmily(JACK,CLUBS);
    emily->add_card(cardOneEmily);
    emily->add_card(cardTwoEmily);
    emily->add_card(cardThreeEmily);
    emily->add_card(cardFourEmily);
    emily->add_card(cardFiveEmily);
    Card leadCardEmily(NINE,CLUBS);
    ASSERT_EQUAL(emily->play_card(leadCardEmily,CLUBS),cardFiveEmily);
    delete emily;

}

TEST(left_bower_follows_suit)
{
    Player* emily=Player_factory("emily","Simple");
    Card cardOneEmily(TEN,HEARTS);
    Card cardTwoEmily(KING,HEARTS);
    Card cardThreeEmily(ACE,HEARTS);
    Card cardFourEmily(QUEEN,HEARTS);
    Card cardFiveEmily(JACK,CLUBS);
    emily->add_card(cardOneEmily);
    emily->add_card(cardTwoEmily);
    emily->add_card(cardThreeEmily);
    emily->add_card(cardFourEmily);
    emily->add_card(cardFiveEmily);
    Card leadCardEmily(NINE,SPADES);
    ASSERT_EQUAL(emily->play_card(leadCardEmily,leadCardEmily.get_suit()),cardFiveEmily);
    delete emily;
}


TEST_MAIN()
