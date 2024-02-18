using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Calculator.Calculators
{
    interface ICalculator
    {
        double Calculate(string expression);
        double TakePercentage(string number);
        double CalculateReciprocal(string number);
        double CalculateSquare(string number);
        double CalculateSquareRoot(string number);
    }
}
