# crypto-portfolio-manager
Educational C++ application demonstrating Object-Oriented Programming principles through practical cryptocurrency portfolio management. Features abstraction, inheritance, polymorphism, encapsulation, file I/O, and intelligent rebalancing algorithms.

## 📋 Short Description

An educational C++ application demonstrating advanced **Object-Oriented Programming concepts** through a practical cryptocurrency portfolio manager. Features include holdings tracking, target allocation management, portfolio valuation, and intelligent rebalancing suggestions with persistent file storage.

## ✨ Key Features

- **📊 Portfolio Tracking**: Manage multiple cryptocurrency holdings
- **🎯 Target Allocation**: Set and monitor investment targets
- **💰 Real-time Valuation**: Calculate portfolio value in USD
- **⚖️ Smart Rebalancing**: Get automated buy/sell suggestions
- **💾 Persistent Storage**: File-based data management
- **🎨 Clean Architecture**: Pure OOP implementation

## 🏗️ OOP Concepts Implemented

### 1. **Abstraction**
### 2. **Inheritance**
### 3. **Polymorphism**
### 4. **Encapsulation**

## 🛠️ Technologies Used

- **Language**: C++11/14
- **STL Containers**: `map`, `vector`, `string`
- **File I/O**: `fstream`, `ifstream`, `ofstream`
- **Design Patterns**: Abstract Factory, Strategy Pattern
- **Data Structures**: Maps for key-value storage

## 📁 Project Structure

```
crypto-portfolio-manager/
├── portfolio_manager.cpp   # Main source code
├── holdings.txt           # User holdings data
├── targets.txt            # Target allocation data
├── ASSIGNMENT.docx        # Detailed project report
├── ASSIGNMENT.pptx        # Project presentation
└── README.md              # This file
```


### Example Workflow

#### Step 1: Add Holdings
```
Select option: 1
Symbol: bitcoin
Quantity: 0.5
Saved holding bitcoin = 0.5
```

#### Step 2: Set Targets
```
Select option: 2
Symbol: bitcoin
Target percent (0-1): 0.6
Saved target bitcoin = 0.6
```

#### Step 3: View Portfolio
```
Select option: 3
Total USD: $15000.00

SYMBOL      QTY         PRICE       VALUE       ALLOC
bitcoin     0.5         30000.00    15000.00    100.00%
```

#### Step 4: Get Rebalancing Advice
```
Select option: 4
Threshold (default 0.05): 0.05
Suggestions (positive=buy USD, negative=sell USD):
  bitcoin      : -6000.00 USD
  ethereum     : 6000.00 USD
```

## 📊 How It Works

### Portfolio Valuation Algorithm

```cpp
Valuation value_portfolio() {
    for each cryptocurrency:
        value = quantity × price
        total_value += value
    
    for each cryptocurrency:
        allocation = (value / total_value) × 100
    
    return {total_value, values, allocations}
}
```

### Rebalancing Logic

```cpp
For each cryptocurrency:
    current_allocation = actual_percentage
    target_allocation = desired_percentage
    difference = current - target
    
    if |difference| > threshold:
        usd_to_trade = -difference × total_portfolio_value
        suggest action
```

## 📈 Sample Output

```
Crypto Portfolio Manager (OOP Clean C++)

1. Add/Update Holding
2. Add/Update Target
3. Show Portfolio
4. Suggest Rebalance
5. Exit

Select option: 3
Total USD: $32420.80

SYMBOL      QTY         PRICE       VALUE       ALLOC
bitcoin     0.20        30000       6000.00     60.00%
ethereum    2.00        2000        4000.00     40.00%

Select option: 4
Threshold (default 0.05): 0.05
Suggestions (positive=buy USD, negative=sell USD):
  bitcoin      : -1000.00 USD
  ethereum     : 1000.00 USD
```

## 🎓 Educational Value

This project teaches:

✅ **Core OOP Principles**
- Abstract classes and interfaces
- Inheritance hierarchies
- Virtual functions and polymorphism
- Encapsulation and data hiding

✅ **Practical C++ Skills**
- STL container usage (`map`, `vector`)
- File I/O operations
- Error handling
- Memory management

✅ **Software Design**
- Clean code principles
- Modular architecture
- Separation of concerns
- Design patterns

✅ **Real-World Application**
- Portfolio management concepts
- Financial calculations
- Data persistence
- User interaction design

## 🔧 Technical Details

### Data Persistence

Holdings and targets are stored in plain text files:

**holdings.txt**
```
bitcoin 0.5
ethereum 2.0
cardano 1000
```

**targets.txt**
```
bitcoin 0.6
ethereum 0.3
cardano 0.1
```

### Supported Cryptocurrencies

Predefined prices for:
- Bitcoin (BTC): $30,000
- Ethereum (ETH): $2,000
- Cardano (ADA): $0.50

*Easily extendable to add more cryptocurrencies*

## 🤝 Contributing

Contributions welcome! Areas for improvement:
- Add more cryptocurrencies
- Implement API integration for live prices
- Add transaction history tracking
- Create GUI interface
- Add unit tests

## 📚 Documentation

For detailed explanation of concepts and implementation, refer to:
- `ASSIGNMENT.docx` - Complete project report
- `ASSIGNMENT.pptx` - Visual presentation
- Code comments - Inline documentation

## 👨‍💻 Authors

**Prince Kachchhi & Akshay Rudakiya**
- Roll No: 24BCE130 & 24BCE132
- Course: Object-Oriented Programming Project
- University:Institute of Technology, Nirma University
