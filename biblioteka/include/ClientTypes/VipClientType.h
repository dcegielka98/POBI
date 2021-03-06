//
// Created by Dominik Cegiełka <224478@edu.p.lodz.pl> on 03.12.2019.
//

#ifndef POBIPROJECT_VIPCLIENTTYPE_H
#define POBIPROJECT_VIPCLIENTTYPE_H

#include "model/ClientType.h"

class VipClientType final : public ClientType{
public:
    VipClientType();

    virtual ~VipClientType();

    const int getNumOfRentalVehicles() const override;

    std::string getClientType() const override;

    const double getDiscount(double RentPrice) const override;
};


#endif //POBIPROJECT_VIPCLIENTTYPE_H
