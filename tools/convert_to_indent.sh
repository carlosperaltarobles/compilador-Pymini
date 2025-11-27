#!/bin/bash
# Script para convertir archivos .pymini de sintaxis con {} a indentación Python

convert_file() {
    local file="$1"
    echo "Convirtiendo: $file"
    
    # Crear backup
    cp "$file" "$file.bak"
    
    # Usar Python para convertir el archivo
    python3 << 'PYTHON_SCRIPT' "$file"
import sys
import re

def convert_pymini_to_indent(input_file):
    with open(input_file, 'r') as f:
        lines = f.readlines()
    
    output_lines = []
    indent_level = 0
    
    for line in lines:
        stripped = line.lstrip()
        
        # Ignorar líneas vacías y comentarios
        if not stripped or stripped.startswith('#'):
            output_lines.append(line.rstrip() + '\n')
            continue
        
        # Detectar aumento de indentación (: {)
        if re.search(r':\s*\{', stripped):
            # Quitar la llave de apertura
            new_line = re.sub(r':\s*\{', ':', stripped)
            output_lines.append('    ' * indent_level + new_line)
            indent_level += 1
            continue
        
        # Detectar cierre de bloque (línea que solo contiene })
        if stripped.strip() == '}':
            indent_level = max(0, indent_level - 1)
            continue
        
        # Detectar cierre de bloque con else/elif (} else { o } elif)
        elif_else_match = re.match(r'\}\s*(elif|else)', stripped)
        if elif_else_match:
            indent_level = max(0, indent_level - 1)
            keyword = elif_else_match.group(1)
            rest = stripped[elif_else_match.end():]
            
            if keyword == 'else':
                # } else: {
                new_line = re.sub(r':\s*\{', ':', 'else' + rest)
                output_lines.append('    ' * indent_level + new_line)
                indent_level += 1
            else:  # elif
                # } elif condicion: {
                new_line = re.sub(r':\s*\{', ':', 'elif' + rest)
                output_lines.append('    ' * indent_level + new_line)
                indent_level += 1
            continue
        
        # Línea normal
        output_lines.append('    ' * indent_level + stripped)
    
    # Escribir resultado
    with open(input_file, 'w') as f:
        f.writelines(output_lines)
    
    print(f"Convertido: {input_file}")

if __name__ == '__main__':
    convert_pymini_to_indent(sys.argv[1])
PYTHON_SCRIPT
}

# Convertir todos los archivos .pymini en tests/
find tests -name "*.pymini" -type f | while read file; do
    convert_file "$file"
done

# Convertir archivos de demo en el directorio raíz
for file in *.pymini; do
    if [ -f "$file" ]; then
        convert_file "$file"
    fi
done

echo "Conversión completada. Los archivos originales están en *.bak"
