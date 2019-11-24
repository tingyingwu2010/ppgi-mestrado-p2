#include "data_reader.h"
#include "bnb_cnb.h"
#include "sub_gradient.h"

int main(int argc, char **argv)
{

    // Leitura da instancia para o bnb
    Data *data = new Data(argc, argv[1]);
    data->readData();
    size_t dim = data->getDimension();

    // Gerando a matriz da instancia (double **)
    double **cost = new double *[dim];
    for (size_t i = 0; i < dim; i++)
    {
        cost[i] = new double[dim];
        for (size_t j = 0; j < dim; j++)
        {
            cost[i][j] = data->getDistance(i, j);
        }
    }

    // GR48
    // double UB = 5046; // otimo!
    double UB = 5048;

    // Metodo de Busca
    int busca = BUSCA_BEST_BOUND;
    // int busca = BUSCA_EM_LARGURA;
    // int busca = BUSCA_EM_PROFUNDIDADE;

    Node solucao = bnbComb(cost, dim, UB, busca);

    // Free memory
    for (size_t i = 0; i < dim; ++i)
    {
        delete[] cost[i];
    }

    // Solucao
    std::cout << std::string(80, '*') << std::endl;
    std::cout << "Solucao: " << solucao.LB << std::endl;

    return 0;
}
