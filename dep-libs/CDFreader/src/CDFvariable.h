#ifndef CDFVARIABLE_H
#define CDFVARIABLE_H

#include "CDFreader.h"
#include "CDFattribute.h"
#include "CDFglobalDefs.h"
#include "CDFerror.h"
#include "cdf.h"

#include <QString>
#include <QStringList>
#include <QMap>
#include <QList>
#include <QVariant>
#include <QPair>



namespace CDFr
{
class CDFattribute;
class CDFreader;
class CDFerrorHandler;

typedef QMap<long, QList<QVariant> > CDFrValueRange;

class CDFvariable
{
public:
    //constructor/destructor
    CDFvariable(CDFr::CDFreader *parent);
    ~CDFvariable();

    //file related information
    CDFreader*          getParent();

    //Variable related information
    QString             getVarName();
    void                setVarName(QString name);

    long                getVarType();
    void                setVarType(long type);

    int64_t             getNumberDims();

    int64_t             getDim(int dim);
    void                setDim(long index, int dimValue);
    long*               getZeroPoint();
    long*               getIntervalDims(long interval);


    int64_t*            getAllDims();
    void                setAllDims(long dims[], int count);

    long                getNumberRecords();
    void                setNumberRecords(long numRecords);

    long                getNumberAtts();
    void                addAttribute(CDFattribute *attribute);

    int64_t             getMonotonicState();
    void                setMonotonicState(long state);


    //actual data
    QVariant            getFillValue();
    void                setFillValue(QVariant fill);

    QVariant            getMinimum();
    void                setMinimum(QVariant minimum);

    QVariant            getMaximum();
    void                setMaximum(QVariant maximum);

    QList<QVariant>     getDataEntry(long index);
    QString             getDataEntryAsDateString(long index, bool iso=false);

    CDFr::CDFrValueRange     getDataRange(long start, long end);

    static QString             getDateStringFromEPOCH(double epoch);
    static QString             getIso8601DateStringFromEPOCH(double epoch);



    //Attributes
    CDFattribute        *getAttribute(int64_t index);
    CDFattribute        *getAttirbute(QString name);

    bool                attributeExists(QString name);


    //index conversions
    inline int64_t      fromXYZ(int64_t x, int64_t y, int64_t z);
    inline int64_t      fromXY(int64_t x, int64_t y);

    long                getDimVaries(long index) const;
    void                setDimVaries(const long value[], long count);

    bool                getRecordVaries() const;
    void                setRecordVaries(bool value);

    void                setAttributeList(CDFr::attributeList Attributes);

    void                setElementReadLength(long numElementsInRow);


protected:
    //file related information
    CDFreader           *parent;

    //Variable Related information
    QString             Name;
    QMap<long, long>    Dims;
    long                VarType;
    long                numberRecords;
    QVariant            fillValue;
    QVariant            minimum;
    QVariant            maximum;
    long                monotonicState;


    //variance status (does the data change?)
    long                recordVaries;               //Data Record Variance
    QList<bool>         dimVaries;                  //Dimensions Variance

    //data related info
    CDFr::attributeList Attributes;         //Variable attributes maped by name

    //memmory managment routines
    bool                allocateRecordMemory(long dataType, void *&data, long numValues);

    //converters
    QVariant            convertVoid2Variant(const void *data, const long dataType, const long index=0);

    CDFrValueRange parseColumMajor(void* data, long start, long numRecords);
    CDFrValueRange parseRowMajor(void* data, long start, long numRecords);
private:
    bool                errorState;
    long                numElementsInRow;



};

long getNumberBytesForType(long cdfType);
}

#endif //CDFVARIABLE_H
