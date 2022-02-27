```

put [/][node[[/node][/node]...][/]

 Creates empty node recursively.

RETURN VALUE

 The put node, thus, an empty node.

ERROR

 If node already exists, nothing is done. In this case the return value is the same as if no errors, but the call gets a HTTP XXX return message.

---

get [/][node[[/node][/node]...][/]

 Returns the last node pointed by the path.

---

del [/][node[[/node][/node]...][/]

 Deletes the last node pointed by the path.

RETURN VALUE

 The node before the deleted one is returned.

ERROR

 If the path is not found, returns (null).

---

post [/][node[[/node][/node]...][/]=value

 Creates a node attribute to the corresponding value.

RETURN VALUE

 Returns the node that have had its value changed.

```
