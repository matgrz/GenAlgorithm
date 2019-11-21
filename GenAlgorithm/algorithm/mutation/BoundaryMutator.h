#pragma once

#include "IMutator.h"

namespace algorithm
{
namespace mutation
{
class BoundaryMutator : public IMutator
{
public:
	BoundaryMutator(int mutationPercentage);
	void mutatePopulation(types::Population&) override;

private:
	void mutateX(types::xValues&);
	void mutateY(types::yValues&);
	bool isLeftBoundryPicked();
};
}
}