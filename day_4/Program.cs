const int ROWS = 5;
const int COLS = 5;
const int CARDS = 100;

using (TextReader reader = File.OpenText("day_4data.txt"))
{
    string[] numbers = reader.ReadLine().Split(',');
    int[] call_nums = new int[numbers.Length];

    for(int i = 0; i < numbers.Length; i++)
    {
        call_nums[i] = int.Parse(numbers[i]);
    }

    int[,,] bingo_cards = new int[ROWS,COLS,CARDS];
    byte[,,] bingo_score = new byte[ROWS,COLS,CARDS];

    int cardID = 0;

    // Fill bingo_cards with numbers
    while (reader.ReadLine() != null)
    {
        for (int row = 0; row < ROWS; row++)
        {
            string[] col_nums = reader.ReadLine().Split(' ', System.StringSplitOptions.RemoveEmptyEntries);

            for (int cols = 0; cols < COLS; cols++)
            {
                bingo_cards[row,cols,cardID] = int.Parse(col_nums[cols]);
            }
        }            
        cardID++;
    }

    int winning_card = -1;
    int winning_called_number = 0;

    // Lets play bingo!
    foreach (int called_number in call_nums)
    {
        mark_your_card(bingo_cards, bingo_score, called_number);

        // check cards for lines
        winning_card = check_for_completed_line(bingo_score);

        if (winning_card != -1)
        {
            winning_called_number = called_number;
            break; // we have a winner
        }
    } 

    int sum_of_unmarked = get_sum_of_unmarked_numbers(bingo_score,bingo_cards,winning_card);
    int result = sum_of_unmarked * winning_called_number;

    Console.WriteLine("\n** Day 4 part one = " + result + " **\n");

    // Lets play again - but this time till the last winner is found 
    int[] card_order_array = new int[CARDS];

    int last_winning_card = -1;
    int last_winning_called_number = 0;

    for (int i = 0; i < CARDS; i++)
        card_order_array[i] = -1;

    int lastest_found_card = 0;

    foreach (int called_number in call_nums)
    {
        mark_your_card(bingo_cards, bingo_score, called_number);

        // check cards for lines
        last_winning_card = mark_order_of_winning_cards(bingo_score, card_order_array, ref lastest_found_card);

        if (last_winning_card != -1)
        {
            last_winning_called_number = called_number;
            break; // we found the last card
        }
    }

    sum_of_unmarked = get_sum_of_unmarked_numbers(bingo_score,bingo_cards,last_winning_card);
    result = sum_of_unmarked * last_winning_called_number;

    Console.WriteLine("** Day 4 part two = " + result + " **\n");
}

void mark_your_card(int[,,] bingo_cards, byte[,,] bingo_score, int called_number)
{
    // search for called number in each card            
    for (int card = 0; card < CARDS; card++)
    {
        for (int row = 0; row < ROWS; row++)
        {
            for (int cols = 0; cols < COLS; cols++)
            {
                if (bingo_cards[row,cols,card] == called_number)
                {
                    // mark your card                            
                    bingo_score[row,cols,card] = 0b1;
                }                        
            }
        }
    }
}

int mark_order_of_winning_cards(byte[,,] bingo_score, int[] card_order_array, ref int found_order)
{
    for (int card = 0; card < CARDS; card++)
    {
        // check if card is already marked
        if (card_order_array[card] != -1)
            continue; 

        int col_0_sum = 0;
        int col_1_sum = 0;
        int col_2_sum = 0;
        int col_3_sum = 0;
        int col_4_sum = 0;

        for (int row = 0; row < ROWS; row++)
        {
            int rowsum = 0;
            for (int col = 0; col < COLS; col++)
            {
                if (bingo_score[row,col,card] == 0b1)
                {
                    // rowsum first - nice and easy                        
                    rowsum++;

                    // cols sums next
                    switch (col)
                    {
                        case 0:
                        {
                            col_0_sum++;
                            break;                                
                        }
                        case 1:
                        {
                            col_1_sum++;
                            break;                                
                        }
                        case 2:
                        {
                            col_2_sum++;
                            break;                                
                        }
                        case 3:
                        {
                            col_3_sum++;
                            break;                                
                        }
                        case 4:
                        {
                            col_4_sum++;
                            break;                                
                        }
                    }

                    if (rowsum == 5 || 
                        col_0_sum == 5 || 
                        col_1_sum == 5 || 
                        col_2_sum == 5 || 
                        col_3_sum == 5 || 
                        col_4_sum == 5) 
                        {
                            // found one!
                            card_order_array[card] = found_order++;
                            // clear counters and carry on - might be more than one winner
                            rowsum = 0; 
                            col_0_sum = 0; 
                            col_1_sum = 0; 
                            col_2_sum = 0; 
                            col_3_sum = 0; 
                            col_4_sum = 0;

                            if (found_order == 100) // last winning card
                                return card;
                        } 
                }
            }
        }
    }
    return -1;
}

int check_for_completed_line(byte[,,] bingo_score)
{
    for (int card = 0; card < CARDS; card++)
    {
        int col_0_sum = 0;
        int col_1_sum = 0;
        int col_2_sum = 0;
        int col_3_sum = 0;
        int col_4_sum = 0;

        for (int row = 0; row < ROWS; row++)
        {
            int rowsum = 0;
            for (int col = 0; col < COLS; col++)
            {
                if (bingo_score[row,col,card] == 0b1)
                {
                    // rowsum first - nice and easy                        
                    rowsum++;

                    // cols sums next
                    switch (col)
                    {
                        case 0:
                        {
                            col_0_sum++;
                            break;                                
                        }
                        case 1:
                        {
                            col_1_sum++;
                            break;                                
                        }
                        case 2:
                        {
                            col_2_sum++;
                            break;                                
                        }
                        case 3:
                        {
                            col_3_sum++;
                            break;                                
                        }
                        case 4:
                        {
                            col_4_sum++;
                            break;                                
                        }
                    }

                    if (rowsum == 5 || 
                        col_0_sum == 5 || 
                        col_1_sum == 5 || 
                        col_2_sum == 5 || 
                        col_3_sum == 5 || 
                        col_4_sum == 5)  
                        return card;
                }
            }
        }
    }
    return -1;
}

int get_sum_of_unmarked_numbers(byte[,,] bingo_score, int[,,] bingo_cards, int winning_card)
{
    int retvalue = 0;

    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            if (bingo_score[row, col, winning_card] == 0)
            {
                retvalue += bingo_cards[row, col, winning_card];
            }
        }
    }
    return retvalue;
}