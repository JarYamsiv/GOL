#include "headers/Grid.h"

//#include<iostream>

Grid::Grid(float cellsize,int W,int H)
{
    this->cellsize=cellsize;
    width=W;
    height=H;
    x=(int)((float)W/cellsize);
    y=(int)((float)H/cellsize);

    mat=new int* [x];
    for(int i=0; i<x; i++)
    {
        mat[i]=new int[y];
    }

    pmat=new int* [x];
    for(int i=0; i<x; i++)
    {
        pmat[i]=new int[y];
    }

    sf::Vector2f sizeof_cell(cellsize,cellsize);
    cell.setSize(sizeof_cell);
}

Grid::~Grid()
{
    //std::cout<<"destroying"<<std::endl;
    for(int i=0; i<x; i++)
    {
        delete[] mat[i];
    }
    delete[] mat;
    mat=0;
    for(int i=0; i<x; i++)
    {
        delete[] pmat[i];
    }
    delete[] pmat;
    pmat=0;
}

void Grid::randomize(int seed)
{
    if(rand()%2==0)
    {srand(seed);}
    for(int i=0; i<x; i++)
    {
        for(int j=0; j<y; j++)
        {
            mat[i][j]=rand()%2;
        }
    }

}

void Grid::update()
{
    int n;
    int im,ip,jm,jp;
    for(int i=0; i<x; i++)
    {
        for(int j=0; j<y; j++)
        {
        n=0;
        im=i-1;ip=i+1;jm=j-1;jp=j+1;

        if(im<0)im=x-1;
        if(ip>=x)ip=0;
        if(jm<0)jm=y-1;
        if(jp>=y)jp=0;

            n=mat[im][jm]+
              mat[i ][jm]+
              mat[ip][jm]+
              mat[im][j ]+
              mat[ip][j ]+
              mat[im][jp]+
              mat[i ][jp]+
              mat[ip][jp];
              //std::cout<<n<<" ";

            if(mat[i][j]==0)
            {
                if(n==3)
                {
                    pmat[i][j]=1;
                }
                else
                {
                    pmat[i][j]=0;
                }
            }

            if(mat[i][j]==1)
            {
                if(n==2||n==3)
                {
                    pmat[i][j]=1;
                }
                else
                {
                    pmat[i][j]=0;
                }
            }
        }
    }
    for(int i=0; i<x; i++)
    {
        for(int j=0; j<y; j++)
        {
            mat[i][j]=pmat[i][j];
        }
    }
}

void Grid::render(sf::RenderWindow* w)
{
    for(int i=0; i<x; i++)
    {
        for(int j=0; j<y; j++)
        {
            cell_pos.x=i*cellsize;
            cell_pos.y=j*cellsize;
            cell.setPosition(cell_pos);
            if(mat[i][j]==1)
            {
                (*w).draw(cell);
            }
        }
    }   

}

void Grid::add_or_remove(int w,int h,bool choice)
{
    int i=w/(int)cellsize;
    int j=h/(int)cellsize;
    if(i>0 && i<x && j>0 && j<y )
    {mat[i][j]=(int)choice;}
}

void Grid::clearMat()
{
    for(int i=0; i<x; i++)
    {
        for(int j=0; j<y; j++)
        {
            mat[i][j]=0;
        }
    }
}