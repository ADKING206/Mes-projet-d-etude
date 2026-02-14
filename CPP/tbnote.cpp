#include <iostream>
using namespace std;
int main()
{
    const int N=5;
    float tabnote[N];
    for(int i=0; i <N;i++)
    {
        do 
        {
        cout<<"donner la note de l'etudiant "<<i+1<<endl;
        cin>>tabnote[i];
        }while(tabnote[i]<20 || tabnote[i]>0);
    }
    return 0;


}