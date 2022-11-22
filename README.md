# Intensive Care Unit System

### Installation:
- Clone the repository: `git clone https://github.com/Intensive-Care-Unit/intensive-care-unit`
- Navigate to the repo's folder: `cd intensive-care-unit`
- Create a `build` folder and navigate to it: `mkdir build && cd build`
- Run the cmake configuration setup: `cmake ..`
- Compile the project: `make -j${nproc}`
- Now you'll have all the project's parts compiled in this file structure
```
├── data
│   └── names.csv
├── AVL
│   ├── AvlTreeTest (run this if you want to test execution time of the AVL Tree patients ADT)
│   └── data
│       └── names.csv
├── BST
│   ├── BinaryTreeTest (run this if you want to test execution time of the BST patients ADT)
│   └── data
│       └── names.csv
├── Hashmap
│   ├── HashMapTest (run this if you want to test execution time of the Hashmap patients ADT)
│   ├── Makefile
│   └── data
│       └── names.csv
├── CareUnitSystem (run this if you want to test the main driver)
```