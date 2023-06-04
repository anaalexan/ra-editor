#pragma once

#include "Relation.h"

using namespace std;
/** Class for managing export into and import from files contains relations   */
class CFileService{
    public:
        CFileService() = default;
        /**
	 * Method for export results of from RA evaluation
	 * @param[in] data shared pointer of {@link #CRelation} class contains result relation from evaluation to export
     * @returns true in case method succeeded to export, false otherwise
	 */
        bool exportToFile(shared_ptr<CRelation> data); 

        /**
	 * Method for import relation to evaluate expression in RA
	 * @param[in] data shared pointer of {@link #CRelation} class contains path to import data
     * @returns true in case method succeeded to import, false otherwise
	 */
        bool importFromFile(const shared_ptr<CRelation> & data);

        /**
	 * Method for import only atributes of the relation to evaluate expression in RA
	 * @param[in] data shared pointer of {@link #CRelation} class contains path to import data
     * @returns true in case method succeeded to import, false otherwise
	 */
        CRow importAtriburesFromFile(const shared_ptr<CRelation> & data);

};