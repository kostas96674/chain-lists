//
// Created by Dimitris on 09/05/2021.
//

#include <functional>
#include <random>
#include "Chain.h"

default_random_engine generator;
uniform_int_distribution<int> list_size_distribution(100, 200);
uniform_int_distribution<int> data_element_distribution(0, 50);
auto random_list_size = bind(list_size_distribution, generator);
auto random_element = bind(data_element_distribution, generator);

void outputMethod(Chain<int>& output, Chain<int> L[], int K);

int main() {

    int K; // k chain lists

    cout << "Give the number of chain lists:\n";
    cin >> K;

    while(K < 1) {

        cout << "Wrong input, give the number of chain lists:\n";
        cin >> K;

    }

    auto *L = new Chain<int>[K]; // == L<int> L[K];
    Chain<int> output; // output chain list

    for(int i=0; i<K; ++i) {

       int list_size = random_list_size(); // Random list size.

        for (int j=0; j<list_size; ++j) {

            int data_element = random_element(); // Random data element.
            L[i].Insert(j, data_element); // Insert data_element after j'th node.

        }

    }

    outputMethod(output, L, K);
    cout << "Output: " << output;

    return 0;

}

void outputMethod(Chain<int>& output, Chain<int> L[], int K) { // This function find the elements which appear in at least
// half of the chain lists, delete the identical elements from the other chain lists and sort them by ascending in output list.
    int data, i = 0;

    while((K % 2 == 0) ? (i < K/2+1) : (i <= K/2+1)) { // When i is bigger than K/2, no more numbers can be added to the output list.
                                                       // If K is an even number, i < K/2+1 else i <= K/2+1.
        while(L[i].Length()) { // While L[i] is not empty.
                                    // counter counts how many times we found the specific data in each chain list.
            int counter = 0, g = i; // g starts from i because the previous chain lists are deleted.
            L[i].Find(1, data); // Return in data variable the first element of each chain list.

            while (g < K) { // Search if data contained in the other chain lists
                            // and delete the repetitive elements from the chain lists.
                bool found, flag = true;

                if(L[g].IsEmpty()) { // If L[g] is empty continue to the next chain list.

                    g++;
                    continue;

                }

                    do {

                    if(L[g].Search(data)) { // if (L[g].Search(data) != 0)
                    // If data was found in L[g], delete it.
                        L[g].Delete(L[g].Search(data));
                        found = true;

                    } else flag = false;

                } while(L[g].Length() && flag); // When the length == 0 or flag == false, exit.

                found ? ++counter : counter;
                g++;

            }

            if(counter >= K / 2) { // If data appears in half or more of the lists,
                                   // insert it in ascending order in output list.
                int last, size = output.Length();

                if(output.IsEmpty()) // If output list is empty, last = -1.
                    last = -1;

                else output.Find(size, last); // Else if not empty, last = last element of output list.

                if (output.IsEmpty() || (last > data && size == 1)) // If output list is empty, or data is less than the
                    output.Insert(0, data); // first element of output list and list size is 1, insert data at the beginning.

                else if(last < data) // If data is bigger than the last element of output list,
                    output.Insert(size, data); //  insert data after last element.

                else
                    for (int a=1; a<=size-1; ++a) { // Starts from the first element until the n-1'th.

                        int temp, temp2, b = a + 1;
                        output.Find(a, temp);
                        output.Find(b, temp2);

                        if(temp > data && temp2 > data) { // Check if data is less than the a'th and a+1'th elements

                            output.Insert(a - 1, data); // and insert it before the a'th element.
                            break;

                        } else if(temp < data && temp2 > data) { // Check if data is between the a'th and a+1'th elements,

                            output.Insert(a, data); // and insert it between them.
                            break;

                        } else continue; // Else check for the next elements in output list.

                    }

            }

        }

        i++;

    }

}
