#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include "aux_structs.hpp"
#include "pareto_f.hpp"
using namespace std;


int main(){
    srand(time(NULL));
    int n=256,nn=4;
    std::vector<tff> time_eff(nn),time_ineff(nn);
    for(int i=0;i<nn;i++){
        n=(n<<i);
        vector<tii> a;
        a=curv_nd2(n);
        printf_file("Puntos2D.txt",a);
        vector<tii> pareto;
        double t1=clock();
        dominancia_eficiente(a,pareto);
        double toc=(clock()-t1)/CLOCKS_PER_SEC;
        printf("Para %d individuos 2D El eficiente tarda %e segundos\n",n,toc);
        printf_file("Pareto2D.txt",pareto);
        time_eff.emplace_back(std::make_tuple(n,toc));
        a=curv_rand2(n);
        t1=clock();
        pareto=dominancia_ineficiente(a); 
        toc=(clock()-t1)/CLOCKS_PER_SEC;
        time_ineff.emplace_back(std::make_tuple(n,toc));
        printf("Para %d individuos 2D El ineficiente tarda %e segundos\n",n,toc);
    }
    printf_file("2D_inef_times.txt",time_ineff);
    printf_file("2D_efff_times.txt",time_eff);
    time_eff.clear();
    time_ineff.clear();
    n=256;
    printf("\n\n\n");
    for(int i=0;i<nn;i++){
        n=n<<i;
        vector<tiii> a;
        a=curv_rand(n);
        //sort(a.begin(),a.end());
        std::vector<tiii> pareto;
        double t1=clock();
        dominancia_eficiente(a,pareto);
        double toc=(clock()-t1)/CLOCKS_PER_SEC;
        printf("Para %d individuos 3D el eficiente tarda %e segundos\n",n,toc);
        time_eff.emplace_back(std::make_tuple(n,toc));
        a=curv_rand(n);
        t1=clock();
        pareto=dominancia_ineficiente(a);
        toc=(clock()-t1)/CLOCKS_PER_SEC;
        //printf_file("Puntos3D.txt",a);
        printf("Para %d individuos 3D el ineficiente tarda %e segundos\n",n,toc);
        time_ineff.emplace_back(std::make_tuple(n,toc));
        //printf_file("Pareto3D.txt",pareto);
    }
    printf_file("3D_inef_times.txt",time_ineff);
    printf_file("3D_efff_times.txt",time_eff);
    return 0;
}