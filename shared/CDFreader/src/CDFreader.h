#ifndef CDFREADER_H
#define CDFREADER_H

#include "CDFattribute.h"
#include "CDFvariable.h"
#include "CDFBadDataHandler.h"
#include "CDFerror.h"
#include "CDFglobalDefs.h"

#include <QString>
#include <QMap>
#include <QList>
#include <QVariant>

#include "cdf.h"



namespace CDFr
{

class CDFvariable;
class CDFattribute;
class CDFbadDataHandler;
class CDFerrorHandler;


class CDFreader
{
public:
    //creator/destructor
    CDFreader(QString FileName);
    ~CDFreader();

    //data related infromation
    /* Variables */
    QString           getVarName(int index);
    QStringList       getVarNames();
    long getNumberVariables();
    CDFvariable*      getVariable(int index);
    CDFvariable*      getVariable(QString name);

    /* Global Attributes */
    QString           getGlobalAttName(int index);
    QStringList       getGlobalAttNames();
    long getNumberGlobalAttributes();
    CDFattribute*     getGlobalAttribute(int index);
    CDFattribute*     getGlobalAttribute(QString name);


    //file related information
    QString     getFileName();
    long    getCompressionType();
    long    getChecksum();
    long getFormat();
    long getEncoding();
    QVariant    getCdfVersion();
    bool        isRowMajor();

    //handlers
    void        setBadDataHandler(CDFr::CDFbadDataHandler *handler);

    //error handling
    bool    hasError();         //if there is an error or not
    QString getErrorString();   //returns the error string for the current error

protected:

    //File Related information
    QString     FileName;
    QString     Copyright;
    long        CompressionType;
    QList<long> CompressionParms;
    long        CompressionPercentage;
    long        Format;
    long        Checksum;
    long        Encoding;
    long        cdfVersion;
    long        cdfRelease;
    long        cdfIncrement;
    long        majority;

    //data related information
    QMap<QString, CDFvariable*>     Variables;
    QMap<QString, CDFattribute*>    Attributes;

    //Handlers
    CDFr::CDFbadDataHandler*        BadDataHandler;


private:
    CDFr::CDFerrorHandler*   errorTracker;
    bool setErrorStatus(CDFstatus status);
    void processAttribute(const long dataType, const long numElemets, const long attN, const long entryN ,QVariant &Data);

};
}


#endif //CDFREADER_H
