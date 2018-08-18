#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

char char_matrix = 'z';
char pointerMatrix_M[100][100];
char pointerMatrix_X[100][100];
char pointerMatrix_Y[100][100];
string seq1, seq2;

int match_char(char Sa, char Sb, int match_score, int mis_match_score);
int max_score(int MScore, int XScore, int YScore);
string* BackTrace(int max_matrix_1, int max_matrix_2, char char_M, string seq_1,string seq_2);
int Recursion(int temp_x, int temp_y, char char_M, string seq_1, string seq_2);
void ReverseString();
void ReverseString2();
void print_final(string first_sequence, string second_sequence, int length_first_sequence, int length_second_sequence);

int main()
{
  string first_sequence, second_sequence;
  int match_score, gap_starting, gap_extend;
  int mis_match_score, max_value = 0;
  int length_first_sequence = 0;
  int length_second_sequence = 0;
  int max_matrix[3];
  char char_matrix_1 = 'z';

  cout <<"Enter the first sequence   ";
  cin >> first_sequence;
  cout <<"Enter the second sequence   ";
  cin >> second_sequence;
  cout << "Enter the match score   ";
  cin >> match_score;
  cout << "Enter the mismatch score   ";
  cin >> mis_match_score;
  cout << "Enter the starting gap score   ";
  cin >> gap_starting;
  cout << "Enter the extending gap score   ";
  cin >> gap_extend;

  float infinity = -1 * numeric_limits<float>::infinity();

  length_first_sequence = first_sequence.length();
  length_second_sequence = second_sequence.length();

  float M[100][100];
  float X[100][100];
  float Y[100][100];

  M[0][0] = 0;
  X[0][0] = 0;
  Y[0][0] = 0;

  for(int i=1; i<=length_second_sequence; i++)
  {
    M[0][i] = infinity;
    X[0][i] = gap_starting + ((i-1) * gap_extend);
    Y[0][i] = infinity;
  }
  for(int i=1; i<=length_first_sequence; i++)
  {
    M[i][0] = infinity;
    X[i][0] = infinity;
    Y[i][0] = gap_starting + ((i-1) * gap_extend);
  }

  for (int i = 1; i < length_first_sequence+1; i++)
  {
    for(int j = 1; j < length_second_sequence+1; j++)
    {
      M[i][j] = match_char(first_sequence[i-1], second_sequence[j-1], match_score, mis_match_score) +
        max_score(M[i-1][j-1], X[i-1][j-1], Y[i-1][j-1]);
        pointerMatrix_M[i][j] = char_matrix;

      X[i][j] = max_score((M[i][j-1] + gap_starting), (X[i][j-1] + gap_extend),
        (Y[i][j-1] + gap_starting));
        pointerMatrix_X[i][j] = char_matrix;

      Y[i][j] = max_score((M[i-1][j] + gap_starting), (X[i-1][j] + gap_starting),
        (Y[i-1][j] + gap_extend));
        pointerMatrix_Y[i][j] = char_matrix;

      max_value = max_score(M[i][j],X[i][j],Y[i][j]);

      int X = i;
      int Y = j;
      if(max_value >= max_matrix[0])
      {
        max_matrix[0] = max_value;
        max_matrix[1] = X;
        max_matrix[2] = Y;
        char_matrix_1 = char_matrix;
      }
    }
  }
  cout << "Optimaum alignment score is   " << max_matrix[0] << endl;
  string* final_sequence = BackTrace(length_first_sequence, length_second_sequence, char_matrix_1, first_sequence, second_sequence);

  // printing the matrix
  cout << endl << endl << "*****M(i,j)*****" << endl;
  for(int i=0; i<=length_first_sequence; i++)
  {
    for(int j=0; j<=length_second_sequence; j++)
    {
      cout << M[i][j] << "\t";
    }
    cout << endl;
  }

  cout << endl << endl << "*****X(i,j)*****" << endl;
  for(int i=0; i<=length_first_sequence; i++)
  {
    for(int j=0; j<=length_second_sequence; j++)
    {
      cout << X[i][j] << "\t";
    }
    cout << endl;
  }

  cout << endl << endl << "*****Y(i,j)*****" << endl;
  for(int i=0; i<=length_first_sequence; i++)
  {
    for(int j=0; j<=length_second_sequence; j++)
    {
      cout << Y[i][j] << "\t";
    }
    cout << endl;
  }

  return 0;
}

int match_char(char Sa, char Sb, int match_score, int mis_match_score)
{
  int score;
  if (Sa == Sb) {
    score = match_score;
  } else {
    score = mis_match_score;
  }
  return score;
}
int max_score(int MScore, int XScore, int YScore)
{
  int max_score = 0;
  if(MScore >= XScore && MScore >= YScore)
  {
    max_score = MScore;
    char_matrix = 'm';
  }
  else if(XScore >= MScore && XScore >= YScore)
  {
    max_score = XScore;
    char_matrix = 'x';
  }
  else
  {
    max_score = YScore;
    char_matrix = 'y';
  }
  return max_score;
}

string* BackTrace(int max_matrix_1, int max_matrix_2, char char_M, string seq_1,string seq_2)
{
  string* final_sequence = new string[2];
  int temp_x = max_matrix_1;
  int temp_y = max_matrix_2;
  seq1 += seq_1[temp_x-1];
  seq2 += seq_2[temp_y-1];
  char present_char;

  if(char_M == 'm')
  {
    present_char = pointerMatrix_M[temp_x][temp_y];
    temp_x--;
    temp_y--;

  }
  else if(char_M == 'x')
  {
    present_char = pointerMatrix_M[temp_x][temp_y];
    temp_y--;

  }
  else
  {
    present_char = pointerMatrix_M[temp_x][temp_y];
    temp_x--;
  }
  Recursion(temp_x, temp_y, present_char, seq_1, seq_2);

  ReverseString();
  ReverseString2();
  cout << "Sequence 1   " << seq1 << endl;
  cout << "sequence 2   " << seq2 << endl;
  final_sequence[0] = seq1;
  final_sequence[1] = seq2;
  return final_sequence;
}

int Recursion(int temp_x, int temp_y, char present_char, string seq_1, string seq_2)
{
  if ((temp_x == 0 && temp_y == 0) || (temp_x < 0 || temp_y < 0))
  {
    return 1;
  }
  else {
    if (present_char == 'm') {
       present_char = pointerMatrix_M[temp_x][temp_y];
       if (temp_x >= 1 && temp_y >= 1) {
         seq1 += seq_1[temp_x - 1];
         seq2 += seq_2[temp_y - 1];
       }
       temp_x--;
       temp_y--;
       return Recursion( temp_x, temp_y, present_char, seq_1, seq_2);
    }
    else if (present_char == 'x') {
      present_char = pointerMatrix_M[temp_x][temp_y];
      if (temp_x >= 1) {
        seq1 += '_';
        seq2 += seq_2[temp_y - 1];

      }
      temp_y--;
      return Recursion( temp_x, temp_y, present_char, seq_1, seq_2);
    }
    else {
      present_char = pointerMatrix_Y[temp_x][temp_y];
      if (temp_x >= 1) {
        seq1 += seq_1[temp_x - 1];
        seq2 += '_' ;
      }
      temp_x--;
      return Recursion(temp_x, temp_y, present_char, seq_1, seq_2);
    }
  }

}

void ReverseString()
{
  string temp = seq1;
  int last_index = seq1.length()-1;
  for (int i=last_index; i>=0; i--) {
    temp[last_index-i] = seq1[i];
  }
  seq1 = temp;
}
void ReverseString2()
{
  string temp = seq2;
  int last_index = seq2.length()-1;
  for (int i=last_index; i>=0; i--) {
    temp[last_index-i] = seq2[i];
  }
  seq2 = temp;
}
