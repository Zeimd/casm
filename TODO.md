Concept Assembler
------------------------------------------------------------

-------------------
Assembler

- [ ] Add option to use immediate value or displacement together with
      a symbol for struct member access etc

- [ ] Bug fix: Relocation data offsets are incorrect if there's more than one
      code element
 
------------------
Relocationing

- [ ] Add a centralized relocation unit instead of builder, linker and
      executable creation all duplicating it

------------------
Linker

- [ ] Test multiple source object files

- [ ] Update to not modify inputs. Current implementation
      prevents objects being used in subsequent linking operations

------------------
Executable

- [ ] Update to not modify inputs. Current implementation
      prevents objects being used in subsequent executable creation

------------------
Instruction encoder

- [ ] Separate build params into input and output structures


