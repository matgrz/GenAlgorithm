# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

# This is a reminder that you are using a generated .pro file.
# Remove it when you are finished editing this file.
message("You are running qmake on a generated .pro file. This may not work!")


HEADERS += ./GenAlgorithm.h \
    ./algorithm/InputDataParser.h \
    ./algorithm/PopulationManager.h \
    ./algorithm/ServicesFactory.h \
    ./algorithm/types/Bitset.h \
    ./algorithm/types/InputData.h \
    ./algorithm/types/MainTypes.h \
    ./algorithm/types/Mutations.h \
    ./algorithm/types/Crossovers.h \
    ./algorithm/types/SelectionMethods.h \
    ./algorithm/selection/BestIndividualSelector.h \
    ./algorithm/selection/ISelector.h \
    ./algorithm/selection/TournamentSelector.h \
    ./algorithm/crossover/ICrossover.h \
    ./algorithm/crossover/OnePointCrossover.h \
    ./algorithm/mutation/BoundaryMutator.h \
    ./algorithm/mutation/IMutator.h \
    ./algorithm/mutation/OnePointMutator.h
SOURCES += ./GenAlgorithm.cpp \
    ./main.cpp \
    ./algorithm/InputDataParser.cpp \
    ./algorithm/PopulationManager.cpp \
    ./algorithm/ServicesFactory.cpp \
    ./algorithm/selection/BestIndividualSelector.cpp \
    ./algorithm/selection/TournamentSelector.cpp \
    ./algorithm/crossover/OnePointCrossover.cpp \
    ./algorithm/mutation/BoundaryMutator.cpp \
    ./algorithm/mutation/OnePointMutator.cpp
FORMS += ./GenAlgorithm.ui
RESOURCES += GenAlgorithm.qrc