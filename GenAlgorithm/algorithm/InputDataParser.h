#pragma once

#include "ui_GenAlgorithm.h"
#include "types/InputData.h"

namespace algorithm
{
class InputDataParser
{
public:
    types::InputData parseData(const Ui::GenAlgorithmClass& ui);
    types::SelectionMethods parseSelectionMethod(const Ui::GenAlgorithmClass& ui);
    types::Crossovers parseCrossoverMethod(const Ui::GenAlgorithmClass& ui);
    types::Mutations parseMutationMethod(const Ui::GenAlgorithmClass& ui);
};
}
