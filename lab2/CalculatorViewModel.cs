using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Calculator.Mvvm;
using Microsoft.VisualStudio.PlatformUI;
using Prism.Commands;
using System.Windows.Input;
using Calculator.Calculators;

namespace Calculator.ViewModel
{
    public class CalculatorViewModel : BaseViewModel
    {
        public DelegateCommand<object> ButtonPressedCommand { get; set; }
        public DelegateCommand ClearCommand { get; set; }
        public DelegateCommand EqualsCommand { get; set; }
        public DelegateCommand PercentageCommand { get; set; }
        public DelegateCommand EraseCharacterCommand { get; set; }
        public DelegateCommand ReciprocalCommand { get; set; }
        public DelegateCommand SquareCommand { get; set; }
        public DelegateCommand RootCommand { get; set; }
        public DelegateCommand ClearEntryCommand { get; set; }

        private string _expression;
        private bool isCalculated;
        private int _operationIndex;
        private readonly ICalculator _calculator;
        public string Expression
        {
            get => _expression;
            set
            {
                _expression = value;
                OnPropertyChanged(nameof(Expression));

            }

        }
        public CalculatorViewModel()
        {
            ButtonPressedCommand = new DelegateCommand<object>(ButtonPressed);
            ClearCommand = new DelegateCommand(Clear);
            EqualsCommand = new DelegateCommand(Equals);
            PercentageCommand = new DelegateCommand(Percantage);
            EraseCharacterCommand = new DelegateCommand(EraseChar);
            ReciprocalCommand = new DelegateCommand(TakeReciprocal);
            SquareCommand = new DelegateCommand(TakeSquare);
            RootCommand = new DelegateCommand(TakeRoot);
            ClearEntryCommand = new DelegateCommand(ClearEntry);
            

            _calculator = new MyCalculator();
            isCalculated = false;
            _operationIndex = -1;
        }

        private void ClearEntry()
        {
            if (_operationIndex != -1)
            {
                if (_operationIndex == Expression.Length - 1)
                    Clear();
                else
                    Expression = Expression.Remove(_operationIndex + 1);
            }
            else
            {
                Clear();
            }
        }

        private void TakeRoot()
        {
            Expression = _calculator.CalculateSquareRoot(Expression).ToString();
            isCalculated = true;
        }

        private void TakeSquare()
        {
            Expression = _calculator.CalculateSquare(Expression).ToString();
            isCalculated = true;
        }

        private void TakeReciprocal()
        {
            Expression = _calculator.CalculateReciprocal(Expression).ToString();
            isCalculated = true;
        }

        private void EraseChar()
        {
            if (String.IsNullOrEmpty(Expression))
                return;
            char ch = Expression[Expression.Length - 1];
            if (IsOperation(ch))
            {
                _operationIndex = -1;
            }
            Expression = Expression.Remove(Expression.Length - 1, 1);

        }

        private void Percantage()
        {
            Expression = _calculator.TakePercentage(Expression).ToString();
            isCalculated = true;
        }

        private void Equals()
        {
            isCalculated = true;
            _operationIndex = -1;
            try
            {
                Expression = _calculator.Calculate(Expression).ToString();
            }
            catch(Exception e)
            {
                Expression = "Error";
            }
            
        }

        private void Clear()
        {
            Expression = string.Empty;
            _operationIndex = -1;
        }

        private bool IsOperation(char ch)
        {
            if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '÷')
            {
                return true;
            }
            return false;
        }

        private void ButtonPressed(object obj)
        {
            var str = obj.ToString();
            if (isCalculated)
            {
                if (!IsOperation(str[0]))
                {
                    Clear();
                }
                isCalculated = false;
            }

            if (str.ElementAt(0) == 'D' && str.Length == 2)
            {
                Expression += str.Remove(0, 1);
            }
            else if (str.ElementAt(0) == 'N' && str.Length == 7)
            {
                Expression += str.Remove(0, 6);
            }
            else
            {
                switch(str)
                {
                    case "OemPlus":
                    case "Add":
                        Expression += "+";
                        break;

                    case "Multiply":
                        Expression += "*";
                        break;
                    case "Divide":
                    case "÷":
                        Expression += "/";
                        break;
                    case "Subtract":
                        Expression += "-";
                        break;
                    default:
                        Expression += str;
                        break;
                }

                if (str == "OemPlus" || str == "Add" || str == "Multiply" || str == "Divide" || str == "Subtract" || str == "+" || str == "-" || str == "*" || str == "÷")
                {
                    _operationIndex = Expression.Length - 1;
                }
            }
            //Type t = obj.GetType();
            //if (t == typeof(Key))
            //{
               // Key k = (Key)obj;
                //Expression += Key.obj.ToString();
            //}
            
            //OnPropertyChanged(Expression); // not cool

        }

        public string Title { get; } = "MyCalculator";

    }
}
