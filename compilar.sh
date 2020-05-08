#!/bin/bash
clang++ -std=c++1z -stdlib=libc++ -lgmpxx -lgmp -pthread -DPRIME_TESTER_LIB=lib -DBIG_GEARS_FACTORIZER_LIB -DBIG_HALF_GEAR_FACTORIZER_LIB kdutils.cpp argumentsHandler.cpp maths_prime.cpp primeTester.cpp bigFactorObject.cpp bigGearsFactorizer.cpp bigHalfGearFactorizer.cpp aldo2.cpp -o aldo2.out --debug -v
