This project builds a simple server running a CRUD layout.

It is a conceptual thing to be able to manipulate any node for any type.

```

put [/][node[[/node][/node]...][/]

 Creates empty node.
 Returns the empty node.

---

get [/][node[[/node][/node]...][/]

 Returns the parent node.

---

del [/][node[[/node][/node]...][/]

 Returns the parent node, or if not found, null.

---

post [/][node[[/node][/node]...][/]=value

 Returns the newly created node.

```
