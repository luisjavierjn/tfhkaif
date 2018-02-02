
#ifndef _BIXOLON_TRANSLATOR_H_
#define _BIXOLON_TRANSLATOR_H_

namespace Quorion {

class Bixolon
{
public:
    Bixolon();

    ~Bixolon();

	long TextoEnDocumentoNoFiscal(char* trama_bx, char* trama_qp);

	long ReporteX(char* trama_bx, char* trama_qp);

	long ReporteZ(char* trama_bx, char* trama_qp);
};

} // namespace Quorion

#endif // _BIXOLON_TRANSLATOR_H_