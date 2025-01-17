## 动机

* 在软件构建过程中，由于需求的改变，某些类层次结构中常常需要增加新的行为（方法），如果直接在基类中做这样的更改，将会给子类带来很繁重的变更负担，甚至破坏原有设计
* 如何在不更改类层次结构的前提下，在运行时根据需要透明地为类层次结构上的各个类动态添加新的操作，从而避免上述问题？

## 模式定义

表示一个作用于某对象结构中的各元素的操作。使得可以在不改变（稳定）各元素的类的前提下定义（扩展）作用于这些元素的新操作（变化）

## 结构

![在这里插入图片描述](./pics/%E8%AE%BF%E9%97%AE%E8%80%85%E6%A8%A1%E5%BC%8F.jpeg)


## 要点

* Visitor 模式通过所谓双重分发（double dispatch）来实现在不更改（不添加新的操作-编译时）Element 类层次结构的前提下，在运行时透明地为类层次结构上的各个类动态添加新的操作（支持变化）
* 所谓双重分发即 Visitor 模式中间包括了两个多态分发（注意其中的多态机制）：第一个为accept 方法的多态辨析；第二个为 visitElementX 方法的多态辨析
* Visitor 模式的最大缺点在于扩展类层次结构（增添新的Element子类），会导致Visitor 类的改变。因此 Visitor 模式适用于“ Element 类层次结构稳定，而其中的操作却经常面临频繁改动 ”

## 其他示例

https://www.cnblogs.com/suzhou/p/designpattern17visitor.html

## 代码

```cpp
/*
 * C++ Design Patterns: Visitor
 * Author: Jakub Vojvoda [github.com/JakubVojvoda]
 * 2016
 *
 * Source code is licensed under MIT License
 * (for more details see LICENSE)
 *
 */

#include <iostream>

class Element;
class ConcreteElementA;
class ConcreteElementB;

/*
 * Visitor
 * declares a Visit operation for each class of ConcreteElement
 * in the object structure
 */
class Visitor
{
public:
  virtual ~Visitor() {}
  
  virtual void visitElementA( ConcreteElementA* const element ) = 0;
  virtual void visitElementB( ConcreteElementB* const element ) = 0;
  // ...
};

/*
 * Concrete Visitors
 * implement each operation declared by Visitor, which implement
 * a fragment of the algorithm defined for the corresponding class
 * of object in the structure
 */
class ConcreteVisitor1 : public Visitor
{
public:
  ~ConcreteVisitor1() {}
  
  void visitElementA( ConcreteElementA* const )
  {
    std::cout << "Concrete Visitor 1: Element A visited." << std::endl;
  }
  
  void visitElementB( ConcreteElementB* const )
  {
    std::cout << "Concrete Visitor 1: Element B visited." << std::endl;
  }
  // ...
};

class ConcreteVisitor2 : public Visitor
{
public:
  ~ConcreteVisitor2() {}
  
  void visitElementA( ConcreteElementA* const )
  {
    std::cout << "Concrete Visitor 2: Element A visited." << std::endl;
  }
  
  void visitElementB( ConcreteElementB* const )
  {
    std::cout << "Concrete Visitor 2: Element B visited." << std::endl;
  }
  // ...
};

/*
 * Element
 * defines an accept operation that takes a visitor as an argument
 */
class Element
{
public:
  virtual ~Element() {}
  
  virtual void accept( Visitor &visitor ) = 0;
  // ...
};

/*
 * Concrete Elements
 * implement an accept operation that takes a visitor as an argument
 */
class ConcreteElementA : public Element
{
public:
  ~ConcreteElementA() {}
  
  void accept( Visitor &visitor )
  {
    visitor.visitElementA( this );
  }
  // ...
};

class ConcreteElementB : public Element
{
public:
  ~ConcreteElementB() {}
  
  void accept( Visitor &visitor )
  {
    visitor.visitElementB( this );
  }
  // ...
};


int main()
{
  ConcreteElementA elementA;
  ConcreteElementB elementB;
  
  ConcreteVisitor1 visitor1;
  ConcreteVisitor2 visitor2;
  
  elementA.accept(visitor1);
  elementA.accept(visitor2);
  
  elementB.accept(visitor1);
  elementB.accept(visitor2);
  
  return 0;
}

```
