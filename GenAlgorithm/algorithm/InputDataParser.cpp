#include "InputDataParser.h"

#include <iostream>

namespace algorithm
{
types::InputData InputDataParser::parseData(const Ui::GenAlgorithmClass& ui)
{
    types::InputData inputData{};

    inputData.accuracy = ui.textEditAccuracy->toPlainText().toInt();
    inputData.populationSize = ui.textEditPopulationSize->toPlainText().toInt();
    inputData.generationCount = ui.textEditGenerationCount->toPlainText().toInt();
    inputData.inversionProbability = ui.textEditInversionProbability->toPlainText().toInt();
    inputData.strategyPercent = ui.textEditStrategyPercent->toPlainText().toInt();
    inputData.selectionMethod = parseSelectionMethod(ui);
    inputData.selectionParameter = ui.textEditSelectionParam->toPlainText().toInt();
    inputData.crossoverMethod = parseCrossoverMethod(ui);
    inputData.crossoverProbability = ui.textEditCrossoverProbability->toPlainText().toInt();
    inputData.mutationMethod = parseMutationMethod(ui);
    inputData.mutationProbability = ui.textEditMutationProbability->toPlainText().toInt();

    return inputData;
}
types::SelectionMethods InputDataParser::parseSelectionMethod(const Ui::GenAlgorithmClass& ui)
{
    if (ui.radioButtonMS1->isChecked())
        return types::SelectionMethods::BEST_ONES;
    else if (ui.radioButtonMS2->isChecked())
        return types::SelectionMethods::ROULETTE_WHEEL;
    else
        return types::SelectionMethods::TOURNAMEN;
}
types::Crossovers InputDataParser::parseCrossoverMethod(const Ui::GenAlgorithmClass& ui)
{
    if (ui.radioButtonRecomb1->isChecked())
        return types::Crossovers::ONE_POINT;
    else if (ui.radioButtonRecomb2->isChecked())
        return types::Crossovers::TWO_POINT;
    else
        return types::Crossovers::HOMOGENEOUS;
}
types::Mutations InputDataParser::parseMutationMethod(const Ui::GenAlgorithmClass& ui)
{
    if (ui.radioButtonMutation1->isChecked())
        return types::Mutations::BOUNDARY;
    else if (ui.radioButtonMutation2->isChecked())
        return types::Mutations::ONE_POINT;
    else
        return types::Mutations::TWO_POINT;
}
}
