using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Calculator.Calculators
{
    public class MyCalculator : ICalculator
    {
        public double Calculate(string expression)
        {
            var dataTable = new DataTable();
            var answer = dataTable.Compute(expression, "");
            return Convert.ToDouble(answer);
        }

        public double CalculateReciprocal(string number)
        {
            if (String.IsNullOrEmpty(number))
            {
                number = "0";
            }
            return 1.0 / Convert.ToDouble(number);
        }

        public double CalculateSquare(string number)
        {
            if (String.IsNullOrEmpty(number))
            {
                number = "0";
            }
            var num = Convert.ToDouble(number);
            return num * num;
        }

        public double CalculateSquareRoot(string number)
        {
            if (String.IsNullOrEmpty(number))
            {
                number = "0";
            }
            return Math.Sqrt(Convert.ToDouble(number));
        }

        public double TakePercentage(string number)
        {
            if (String.IsNullOrEmpty(number))
            {
                number = "0";
            }
            return Convert.ToDouble(number) / 100.0;
        }
    }
}
