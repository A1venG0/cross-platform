#pragma once
#include "pch.h"
#include "CppUnitTest.h"
#include "VirtualMahine.cpp"
#include "Assembly.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VMTest
{
	TEST_CLASS(VMTest)
	{
	public:
		
		TEST_METHOD(TestAdd)
		{
			VirtualMachine* machine = new VirtualMachine();
			Assembly assembly;
			machine->load(assembly.convert("LOAD r0 10"));
			machine->load(assembly.convert("LOAD r5 -4"));
			machine->add(assembly.convert("ADD r2 r0 r5"));
			short result = machine->get_registry_value(2);
			delete machine;
			Assert::AreEqual((short)6, result);
		}

		TEST_METHOD(TestLoad)
		{
			VirtualMachine* machine = new VirtualMachine();
			Assembly assembly;
			machine->load(assembly.convert("LOAD r7 5"));
			short result = machine->get_registry_value(7);
			delete machine;
			Assert::AreEqual((short)5, result);
		}

		TEST_METHOD(TestAnd)
		{
			VirtualMachine* machine = new VirtualMachine();
			Assembly assembly;
			machine->load(assembly.convert("LOAD r7 5"));
			machine->load(assembly.convert("LOAD r2 3"));
			machine->bitwise_and(assembly.convert("AND r3 r7 r2"));

			short result = machine->get_registry_value(3);
			delete machine;
			Assert::AreEqual((short)1, result);
		}

		TEST_METHOD(TestNot)
		{
			VirtualMachine* machine = new VirtualMachine();
			Assembly assembly;
			machine->load(assembly.convert("LOAD r7 5"));
			machine->bitwise_not(assembly.convert("NOT r7 r7"));

			short result = machine->get_registry_value(7);
			delete machine;
			Assert::AreEqual((short)-6, result);
		}

		TEST_METHOD(TestJump)
		{
			VirtualMachine* machine = new VirtualMachine();
			Assembly assembly;
			machine->load(assembly.convert("LOAD r6 -7"));
			machine->jump(assembly.convert("JMP r6"));

			short result = machine->get_registry_value(8);
			delete machine;
			Assert::AreEqual((short)-7, result);
		}

		TEST_METHOD(TestCondFlag)
		{
			VirtualMachine* machine = new VirtualMachine();
			Assembly assembly;
			machine->load(assembly.convert("LOAD r0 -10"));
			machine->load(assembly.convert("LOAD r5 -4"));
			machine->add(assembly.convert("ADD r2 r0 r5"));
			short result = machine->get_registry_value(9);
			delete machine;
			Assert::AreEqual((short)4, result);
		}
	};
}
