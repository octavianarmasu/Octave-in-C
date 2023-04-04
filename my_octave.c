//Copyright Octavian Armasu 315CAa 2022-2023
#include <stdio.h>
#include <stdlib.h>
int ***alloc_dinamic(int m,int n,int size,int ***x)
{
    //aloca dinamic un tablou tridimensional
    int i;
    if(size==1){
        x=(int***)malloc(size*sizeof(int**));
        if(!x){
            fprintf(stderr, "malloc() failed\n");
            return NULL;
        }
    }
    else{
        x=(int***)realloc(x,sizeof(int**)*size);
        if(!x){
            fprintf(stderr, "realloc() failed\n");
            return NULL;
        }
    }
    x[size-1]=(int**)malloc(m*sizeof(int*));
    if(!x[size-1]){
        fprintf(stderr, "malloc() failed\n");
        return NULL;
    }
    for(i=0;i<m;i++){
        x[size-1][i]=(int*)malloc(n*sizeof(int));
        if(!x[size-1][i]){
            fprintf(stderr, "malloc() failed\n");
            while(--i>=0){
                free(x[size-1][i]);
            }
            free(x[size-1]);
            return NULL;
        }
    }
    return x;    
}
int *alloc_vector_linie(int size, int *vlinie)
{
    //aloca dinamic un vector ce retine numarul de linii ale unei matrice
    if(size==1){
        vlinie=(int*)malloc(size*sizeof(int));
        if(!vlinie){
            fprintf(stderr, "malloc() failed\n");
            return NULL;
        }
    }
    else{
        vlinie=(int*)realloc(vlinie,sizeof(int)*size);
        if(!vlinie){
            fprintf(stderr, "realloc() failed\n");
            return NULL;
        }
    }
    return vlinie;
}
int *alloc_vector_coloana(int size, int *vcoloana)
{
    //aloca dinamic un vector ce retine numarul de coloane ale unei matrice
    if(size==1){
        vcoloana=(int*)malloc(size*sizeof(int));
        if(!vcoloana){
            fprintf(stderr, "malloc() failed\n");
            return NULL;
        }
    }
    else{
        vcoloana=(int*)realloc(vcoloana,sizeof(int)*size);
        if(!vcoloana){
            fprintf(stderr, "realloc() failed\n");
            return NULL;
        }
    }
    return vcoloana;
}
void read(int m,int n,int size,int ***x)
{
    //citeste matricea cu indexul size-1, avand m linii si n coloane
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            scanf("%d",&x[size-1][i][j]);
        }
    }
}
void print(int m,int n,int size,int ***x)
{
    //afiseaza matricea cu indexul size-1
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            printf("%d ",x[size][i][j]);
        }
        printf("\n");
    }
}
int **alloc_matrix_aux(int nrl,int nrc,int **matrix_aux)
{
    //aloca dinamic o matrice
    int i;
    matrix_aux=(int**)malloc(nrl*sizeof(int*));
    if(!matrix_aux){
        fprintf(stderr, "malloc() failed\n");
        return NULL;
    }
    for(i=0;i<nrl;i++){
        matrix_aux[i]=(int*)malloc(nrc*sizeof(int));
        if(!matrix_aux[i]){
            fprintf(stderr, "malloc() failed\n");
            while(--i>=0){
                free(matrix_aux[i]);
            }
            free(matrix_aux);
            return NULL;
        }
    }
    return matrix_aux;
}
void eliberare_matrix_aux(int nrl,int **matrix_aux)
{
    //elibereaza memoria alocate unei matrice
    for(int i=0;i<nrl;i++){
        free(matrix_aux[i]);
    }
    free(matrix_aux);
}
void free_x(int ***x,int size,int *vlinie)
{
    //elibereaza memoria tabloului tridimensional
    int i,j;
    for(i=0;i<size;i++){
        for(j=0;j<vlinie[i];j++){
            free(x[i][j]);
        }
    }
    for(i=0;i<size;i++){
        free(x[i]);
    }
    free(x);
}
int suma(int **a,int m,int n)
{
    //calculeaza suma elementelor unei matrice
    int s=0,i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            if(a[i][j]>0){
                s=s+a[i][j]%10007;
            }
            else{
                s=s+a[i][j]%10007+10007;
            }
        }
    }
    s=s%10007;
    return s;
}
int **multiplication(int **a,int **b,int **c ,int m,int n,int l2)
{
    //inmulteste matricele a si b si rezultatul il pune in matricea c
    int i,j,z;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            c[i][j]=0;
            for(z=0;z<l2;z++){
                if(a[i][z]*b[z][j]>0)
                    c[i][j]+=(a[i][z]*b[z][j])%10007;
                else{
                    c[i][j]=c[i][j]+(a[i][z]*b[z][j]%10007)+10007;
                }
            }
        }
    }
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            c[i][j]=c[i][j]%10007;
        }
    }
    return c;
}
void multiplication_patratic(int **a,int **b,int n)
{
    //inmulteste doua matrice patratice a si b
    int i,j,z;
    int **c=NULL;
    c=alloc_matrix_aux(n,n,c);
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            c[i][j]=0;
            for(z=0;z<n;z++){
                if(a[i][z]*b[z][j]>0)
                    c[i][j]+=(a[i][z]*b[z][j])%10007;
                else{
                    c[i][j]=c[i][j]+(a[i][z]*b[z][j]%10007)+10007;
                }
            }
        }
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            c[i][j]=c[i][j]%10007;
            a[i][j]=c[i][j];
        }
    }
    eliberare_matrix_aux(n,c);

}
void putere(int **a,int n,int p)
{
    //calculeaza ridicarea la putere in timp logaritmic
    int i,j;
    int **aux=NULL;
    aux=alloc_matrix_aux(n,n,aux);
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            aux[i][j]=a[i][j];
        }
    }
    p--;
    while(p>0){
        if(p%2==1){
            multiplication_patratic(a,aux,n);
        }
        multiplication_patratic(aux,aux,n);
        p/=2;
    }
    eliberare_matrix_aux(n,aux);
}
int **redimensionare(int **p,int nrl,int nrc, int *vnrl,int *vnrc)
{
    //functie pentru redimensionarea unei matrice
    int **a=NULL;
    a=alloc_matrix_aux(nrl,nrc,a);
    for(int i=0;i<nrl;i++){
        for(int j=0;j<nrc;j++){
            a[i][j]=p[vnrl[i]][vnrc[j]]; 
        }
    }
    return a;
}
int **transpusa(int **p, int nrl,int nrc)
{
    //functie care transpune o matrice
    int **a=NULL;
    a=alloc_matrix_aux(nrl,nrc,a);
    for(int i=0;i<nrl;i++){
        for(int j=0;j<nrc;j++){
            a[i][j]=p[j][i]; 
        }
    }
    return a;
}
int main()
{
    int ***x=NULL,*vlinie=NULL,*vcoloana=NULL,n,m,size=0,nrl,nrc;
    int i,j,aux,ind1,ind2,ok,power;
    //x reprezinta tabloul tridimensional
    char c;
    scanf("%c",&c);
    while(1){
        ok=0;
        //variabila ce verifica daca litera primita corespunde unei comenzi
        if(c=='L'){
            ok=1;
            size++;
            //contorizeaza numarul de matrice
            scanf("%d%d",&m,&n);
            x=alloc_dinamic(m,n,size,x);
            vlinie=alloc_vector_linie(size,vlinie);
            vcoloana=alloc_vector_coloana(size,vcoloana);
            vlinie[size-1]=m;
            vcoloana[size-1]=n;
            read(m,n,size,x);
        }
        if(c=='D'){
            ok=1;
            scanf("%d",&aux);
            if(aux>size-1 || aux<0){
                printf("No matrix with the given index\n");
            }
            else{
                printf("%d %d\n",vlinie[aux],vcoloana[aux]);
            }
        }
        if(c=='P'){
            ok=1;
            scanf("%d",&aux);
            if(aux>size-1 || aux<0){
                printf("No matrix with the given index\n");
            }
            else{
                print(vlinie[aux],vcoloana[aux],aux,x);
            }
        }
        if(c=='C'){
            ok=1;
            scanf("%d",&aux);
            scanf("%d",&nrl);
            int *vnrl=(int*)malloc(nrl*sizeof(int));
            //vectorul retine valorile liniilor pe care le vom folosi la resize
            for(i=0;i<nrl;i++){
                scanf("%d",&vnrl[i]);
            }
            scanf("%d",&nrc);
            int *vnrc=(int*)malloc(nrc*sizeof(int));
            //retine valorile coloanelor pe care le vom folosi la resize
            for(i=0;i<nrc;i++){
                scanf("%d",&vnrc[i]);
            }
            if(aux>size-1 || aux<0){
                printf("No matrix with the given index\n");
            }
            else {
                int **p=x[aux];
                //p este o matrice auxiliara care pointeaza la vechea matrice x[aux]
                //folosim p ca sa eliberam memoria matricei x[aux]
                if(!p){
                    fprintf(stderr, "malloc() failed\n");
                    exit(0);
                }
                int **matrix_aux=redimensionare(p,nrl,nrc,vnrl,vnrc);
                //matrix_aux este o matrice auxiliara
                //in matrix_aux construim noua matrice redimensionata
                x[aux]=matrix_aux;
                for(i=0;i<vlinie[aux];i++){
                    free(p[i]);
                }
                free(p);
                vlinie[aux]=nrl;
                vcoloana[aux]=nrc;
            }
            free(vnrc);
            free(vnrl);
        }
        if(c=='T'){
            ok=1;
            scanf("%d",&aux);
            if(aux>size-1 || aux<0){
                printf("No matrix with the given index\n");
            }
            else{
                nrc=vlinie[aux];
                nrl=vcoloana[aux];
                int **p=x[aux];
                //p este o matrice auxiliara care pointeaza la vechea matrice x[aux]
                //folosim p ca sa eliberam memoria matricei x[aux]
                if(!p){
                    fprintf(stderr, "malloc() failed\n");
                    exit(0);
                }
                int **matrix_aux=transpusa(p,nrl,nrc);
                //matrix_aux este o matrice auxiliara in care construim transpusa
                x[aux]=matrix_aux;
                for(i=0;i<vlinie[aux];i++){
                    free(p[i]);
                }
                free(p);
                vlinie[aux]=nrl;
                vcoloana[aux]=nrc;
            }
        }
        if(c=='M'){
            ok=1;
            scanf("%d%d",&ind1,&ind2);
            //ind1 este indecele primei matrice
            //ind2 este indecele celei de a doua matrice
            if(ind1>size-1 || ind2>size-1 || ind1<0 || ind2<0){
                printf("No matrix with the given index\n");
            }
            else{
                if(vcoloana[ind1]!=vlinie[ind2]){
                    printf("Cannot perform matrix multiplication\n");
                }
                else{
                    size++;
                    m=vlinie[ind1];
                    n=vcoloana[ind2];
                    x=alloc_dinamic(m,n,size,x);
                    //alocam o noua matrice in care va fi pus rezultatul
                    vlinie=alloc_vector_linie(size,vlinie);
                    vcoloana=alloc_vector_coloana(size,vcoloana);
                    vlinie[size-1]=m;
                    vcoloana[size-1]=n;
                    int l2=vlinie[ind2];
                    x[size-1]=multiplication(x[ind1],x[ind2],x[size-1],m,n,l2);
                }
            }
        }
        if(c=='F'){
            ok=1;
            scanf("%d",&aux);
            if(aux>size-1 || aux<0){
                printf("No matrix with the given index\n");
            }
            else{
                eliberare_matrix_aux(vlinie[aux],x[aux]);
                for(i=aux;i<size-1;i++){
                    x[i]=x[i+1];
                    vlinie[i]=vlinie[i+1];
                    vcoloana[i]=vcoloana[i+1];
                }
                vlinie=(int *)realloc(vlinie, (size-1)*sizeof(int));
                vcoloana=(int *)realloc(vcoloana, (size-1)*sizeof(int));
                x=(int ***)realloc(x,(size-1)*sizeof(int**));
                //realocam memorie tabloului si vectorilor de line si coloana
                //realocam pentru ca am eliminat o matrice
                //si am eliminat si numarul ei de linii si coloane
                size--;
            }
        }
        if(c=='O'){
            ok=1;
            for(i=0;i<size-1;i++){
                for(j=i+1;j<size;j++){
                    if(suma(x[i],vlinie[i],vcoloana[i])>suma(x[j],vlinie[j],vcoloana[j])){
                        int **p=x[i];
                        //matrice auxiliare care ne ajuta la interschimbare
                        x[i]=x[j];
                        x[j]=p;
                        int v=vlinie[i];
                        //variabila auxiliar care ne ajuta la interschimbarre
                        vlinie[i]=vlinie[j];
                        vlinie[j]=v;
                        v=vcoloana[i];
                        vcoloana[i]=vcoloana[j];
                        vcoloana[j]=v;
                    }
                }
            }
        }
        if(c=='Q'){
            ok=1;
            free_x(x,size,vlinie);
            free(vlinie);
            free(vcoloana);
            break;
        }
        if(c=='R'){
            ok=1;
            scanf("%d%d",&aux,&power);
            if(aux>size-1 || aux<0){
                printf("No matrix with the given index\n");
            }
            else{
                if(power<0){
                    printf("Power should be positive\n");
                }
                else{
                    if(vlinie[aux]!=vcoloana[aux]){
                        printf("Cannot perform matrix multiplication\n");
                    }
                    else{
                        nrl=vlinie[aux];
                        putere(x[aux],nrl,power);
                    }
                }
            }
        }
        if(ok==0){
            //daca ok ramane 0 inseamna ca nu a fost data o comanda corecta
            printf("Unrecognized command\n");
        }
        scanf(" %c",&c);
    }
    return 0;
}