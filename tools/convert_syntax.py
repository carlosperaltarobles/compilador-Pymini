#!/usr/bin/env python3
"""
Convierte archivos .pymini de sintaxis con {} a indentación Python
"""

import sys
import re
import os
from pathlib import Path

def convert_pymini_to_indent(content):
    """Convierte el contenido de un archivo .pymini de {} a indentación"""
    lines = content.split('\n')
    output_lines = []
    indent_level = 0
    
    for i, line in enumerate(lines):
        stripped = line.lstrip()
        
        # Líneas vacías y comentarios se mantienen sin cambios
        if not stripped or stripped.startswith('#'):
            output_lines.append(line.rstrip())
            continue
        
        # Detectar llave de apertura sola en su línea
        if stripped.strip() == '{':
            indent_level += 1
            continue
        
        # Detectar cierre de bloque seguido de else/elif: } else { o } elif cond {
        elif_else_match = re.match(r'^\s*\}\s*(elif|else)', stripped)
        if elif_else_match:
            # Reducir indentación por el cierre de bloque
            indent_level = max(0, indent_level - 1)
            
            keyword = elif_else_match.group(1)
            rest = stripped[elif_else_match.end():].lstrip()
            
            if keyword == 'else':
                # } else: { -> else:
                new_line = re.sub(r':\s*\{.*$', ':', 'else:' if ':' in rest else 'else: ' + rest)
                output_lines.append('    ' * indent_level + new_line.rstrip())
                indent_level += 1
            else:  # elif
                # } elif condicion: { -> elif condicion:
                new_line = re.sub(r':\s*\{.*$', ':', 'elif ' + rest)
                output_lines.append('    ' * indent_level + new_line.rstrip())
                indent_level += 1
            continue
        
        # Detectar cierre de bloque simple: }
        if stripped.strip() == '}':
            indent_level = max(0, indent_level - 1)
            continue
        
        # Detectar apertura de bloque en la misma línea: : {
        if re.search(r':\s*\{', stripped):
            # Quitar la llave de apertura
            new_line = re.sub(r':\s*\{.*$', ':', stripped)
            output_lines.append('    ' * indent_level + new_line.rstrip())
            indent_level += 1
            continue
        
        # Línea normal
        output_lines.append('    ' * indent_level + stripped.rstrip())
    
    return '\n'.join(output_lines) + '\n'

def convert_file(filepath):
    """Convierte un archivo .pymini"""
    print(f"Convirtiendo: {filepath}")
    
    # Leer contenido original
    with open(filepath, 'r', encoding='utf-8') as f:
        original_content = f.read()
    
    # Crear backup
    backup_path = str(filepath) + '.bak'
    with open(backup_path, 'w', encoding='utf-8') as f:
        f.write(original_content)
    
    # Convertir
    converted_content = convert_pymini_to_indent(original_content)
    
    # Escribir resultado
    with open(filepath, 'w', encoding='utf-8') as f:
        f.write(converted_content)
    
    print(f"  ✓ Convertido (backup: {backup_path})")

def main():
    base_dir = Path(__file__).parent.parent  # Subir al directorio raíz
    
    # Buscar todos los archivos .pymini
    pymini_files = []
    
    # En tests/
    tests_dir = base_dir / 'tests'
    if tests_dir.exists():
        pymini_files.extend(tests_dir.rglob('*.pymini'))
    
    # En demos/
    demos_dir = base_dir / 'demos'
    if demos_dir.exists():
        pymini_files.extend(demos_dir.glob('*.pymini'))
    
    # En examples/
    examples_dir = base_dir / 'examples'
    if examples_dir.exists():
        pymini_files.extend(examples_dir.glob('*.pymini'))
    
    if not pymini_files:
        print("No se encontraron archivos .pymini")
        return
    
    print(f"Encontrados {len(pymini_files)} archivos .pymini")
    print()
    
    for filepath in sorted(pymini_files):
        convert_file(filepath)
    
    print()
    print("✓ Conversión completada")
    print("Los archivos originales están guardados con extensión .bak")

if __name__ == '__main__':
    main()
