// GitHub Repository Browser Application

class GitHubBrowser {
    constructor() {
        this.currentRepo = null;
        this.currentOwner = null;
        this.fileTree = [];
        this.monacoEditor = null;
        this.currentFile = null;
        this.allFiles = [];
        
        this.fileIcons = {
            'folder': '📁',
            'file': '📄',
            'js': '📜',
            'javascript': '📜',
            'py': '🐍',
            'python': '🐍',
            'java': '☕',
            'cpp': '⚙️',
            'c': '⚙️',
            'h': '⚙️',
            'hpp': '⚙️',
            'html': '🌐',
            'css': '🎨',
            'json': '📋',
            'md': '📖',
            'markdown': '📖',
            'txt': '📄',
            'xml': '📋',
            'yaml': '📋',
            'yml': '📋',
            'png': '🖼️',
            'jpg': '🖼️',
            'jpeg': '🖼️',
            'gif': '🖼️',
            'svg': '🖼️'
        };

        this.init();
    }

    init() {
        this.setupEventListeners();
        this.initializeMonacoEditor();
    }

    setupEventListeners() {
        // Load repository button
        document.getElementById('loadRepoBtn').addEventListener('click', () => {
            this.loadRepository();
        });

        // Enter key on repo input
        document.getElementById('repoUrl').addEventListener('keypress', (e) => {
            if (e.key === 'Enter') {
                this.loadRepository();
            }
        });

        // File search
        document.getElementById('fileSearch').addEventListener('input', (e) => {
            this.searchFiles(e.target.value);
        });

        // Theme selector
        document.getElementById('themeSelector').addEventListener('change', (e) => {
            this.changeEditorTheme(e.target.value);
        });

        // Download button
        document.getElementById('downloadBtn').addEventListener('click', () => {
            this.downloadCurrentFile();
        });
    }

    async initializeMonacoEditor() {
        try {
            require.config({ paths: { vs: 'https://cdn.jsdelivr.net/npm/monaco-editor@0.45.0/min/vs' } });
            
            require(['vs/editor/editor.main'], () => {
                this.monacoEditor = monaco.editor.create(document.getElementById('monaco-editor'), {
                    value: '',
                    language: 'javascript',
                    theme: 'vs-dark',
                    readOnly: true,
                    automaticLayout: true,
                    minimap: { enabled: false },
                    scrollBeyondLastLine: false,
                    fontSize: 14,
                    lineNumbers: 'on',
                    folding: true,
                    wordWrap: 'on'
                });
            });
        } catch (error) {
            console.error('Failed to initialize Monaco Editor:', error);
        }
    }

    parseRepoUrl(url) {
        const patterns = [
            /github\.com\/([^\/]+)\/([^\/]+)/,
            /^([^\/]+)\/([^\/]+)$/
        ];

        for (const pattern of patterns) {
            const match = url.match(pattern);
            if (match) {
                return {
                    owner: match[1],
                    repo: match[2].replace(/\.git$/, '')
                };
            }
        }
        return null;
    }

    async loadRepository() {
        const repoUrl = document.getElementById('repoUrl').value.trim();
        if (!repoUrl) {
            this.showError('Please enter a repository URL');
            return;
        }

        const repoInfo = this.parseRepoUrl(repoUrl);
        if (!repoInfo) {
            this.showError('Invalid repository URL format. Use: https://github.com/owner/repo or owner/repo');
            return;
        }

        this.showLoading(true);
        
        try {
            // Fetch repository information
            const repoData = await this.fetchRepoInfo(repoInfo.owner, repoInfo.repo);
            this.displayRepoInfo(repoData);
            
            // Set current repo info
            this.currentRepo = repoInfo.repo;
            this.currentOwner = repoInfo.owner;
            
            // Fetch repository contents
            const contents = await this.fetchRepoContents(repoInfo.owner, repoInfo.repo);
            
            // Process and display file tree
            this.fileTree = this.processContents(contents);
            this.renderFileTree();
            
        } catch (error) {
            this.showError(error.message);
        } finally {
            this.showLoading(false);
        }
    }

    async fetchRepoInfo(owner, repo) {
        const response = await fetch(`https://api.github.com/repos/${owner}/${repo}`);
        if (!response.ok) {
            if (response.status === 404) {
                throw new Error('Repository not found. Please check the URL and ensure the repository is public.');
            }
            throw new Error(`Failed to fetch repository: ${response.statusText}`);
        }
        return response.json();
    }

    async fetchRepoContents(owner, repo, path = '') {
        const response = await fetch(`https://api.github.com/repos/${owner}/${repo}/contents/${path}`);
        if (!response.ok) {
            throw new Error(`Failed to fetch repository contents: ${response.statusText}`);
        }
        return response.json();
    }

    displayRepoInfo(repoData) {
        document.getElementById('repoName').textContent = repoData.full_name;
        document.getElementById('repoDescription').textContent = repoData.description || 'No description available';
        document.getElementById('repoStars').textContent = `⭐ ${repoData.stargazers_count}`;
        document.getElementById('repoForks').textContent = `🍴 ${repoData.forks_count}`;
        document.getElementById('repoInfo').style.display = 'block';
    }

    processContents(contents) {
        const processedContents = contents.map(item => ({
            name: item.name,
            path: item.path,
            type: item.type,
            size: item.size,
            download_url: item.download_url,
            sha: item.sha,
            children: null,
            expanded: false
        }));

        // Sort: directories first, then files, both alphabetically
        processedContents.sort((a, b) => {
            if (a.type !== b.type) {
                return a.type === 'dir' ? -1 : 1;
            }
            return a.name.localeCompare(b.name);
        });

        return processedContents;
    }

    renderFileTree() {
        const fileTreeContainer = document.getElementById('fileTree');
        
        if (this.fileTree.length === 0) {
            fileTreeContainer.innerHTML = '<div class="empty-state"><p>No files found in this repository</p></div>';
            return;
        }

        const treeHtml = this.renderTreeItems(this.fileTree, 0);
        fileTreeContainer.innerHTML = treeHtml;
        
        // Add event listeners to file items
        this.attachFileTreeListeners();
    }

    renderTreeItems(items, level) {
        return items.map(item => {
            const icon = this.getFileIcon(item);
            const sizeText = item.type === 'file' ? this.formatFileSize(item.size) : '';
            const hasChildren = item.type === 'dir';
            const expandArrow = hasChildren ? '<span class="expand-arrow">▶</span>' : '<span class="expand-arrow"></span>';
            const marginLeft = level * 20;
            
            let html = `
                <div class="file-item ${item.type}" 
                     data-path="${item.path}" 
                     data-type="${item.type}"
                     data-download-url="${item.download_url || ''}"
                     style="margin-left: ${marginLeft}px"
                     tabindex="0">
                    ${expandArrow}
                    <span class="file-icon">${icon}</span>
                    <span class="file-name">${item.name}</span>
                    ${sizeText ? `<span class="file-size">${sizeText}</span>` : ''}
                </div>
            `;
            
            if (hasChildren && item.children && item.expanded) {
                html += `<div class="file-children" data-parent="${item.path}">`;
                html += this.renderTreeItems(item.children, level + 1);
                html += '</div>';
            }
            
            return html;
        }).join('');
    }

    attachFileTreeListeners() {
        const fileItems = document.querySelectorAll('.file-item');
        
        fileItems.forEach(item => {
            item.addEventListener('click', async (e) => {
                e.stopPropagation();
                
                if (item.dataset.type === 'dir') {
                    await this.toggleDirectory(item);
                } else {
                    this.selectFile(item);
                }
            });

            // Keyboard navigation
            item.addEventListener('keydown', async (e) => {
                if (e.key === 'Enter' || e.key === ' ') {
                    e.preventDefault();
                    if (item.dataset.type === 'dir') {
                        await this.toggleDirectory(item);
                    } else {
                        this.selectFile(item);
                    }
                }
            });
        });
    }

    async toggleDirectory(dirItem) {
        const path = dirItem.dataset.path;
        const arrow = dirItem.querySelector('.expand-arrow');
        
        // Find the directory in our tree structure
        const dirData = this.findItemByPath(this.fileTree, path);
        if (!dirData) return;

        if (!dirData.expanded) {
            // Load directory contents if not already loaded
            if (!dirData.children) {
                try {
                    this.showLoading(true);
                    const contents = await this.fetchRepoContents(this.currentOwner, this.currentRepo, path);
                    dirData.children = this.processContents(contents);
                } catch (error) {
                    this.showError(`Failed to load directory: ${error.message}`);
                    return;
                } finally {
                    this.showLoading(false);
                }
            }
            
            dirData.expanded = true;
            arrow.classList.add('expanded');
        } else {
            dirData.expanded = false;
            arrow.classList.remove('expanded');
        }
        
        // Re-render the tree
        this.renderFileTree();
    }

    findItemByPath(items, targetPath) {
        for (const item of items) {
            if (item.path === targetPath) {
                return item;
            }
            if (item.children) {
                const found = this.findItemByPath(item.children, targetPath);
                if (found) return found;
            }
        }
        return null;
    }

    async selectFile(fileItem) {
        // Remove previous selection
        document.querySelectorAll('.file-item.selected').forEach(item => {
            item.classList.remove('selected');
        });
        
        // Add selection to current item
        fileItem.classList.add('selected');
        
        const filePath = fileItem.dataset.path;
        const downloadUrl = fileItem.dataset.downloadUrl;
        
        if (!downloadUrl) {
            this.showError('Cannot load file content');
            return;
        }
        
        try {
            this.showLoading(true);
            const response = await fetch(downloadUrl);
            
            if (!response.ok) {
                throw new Error(`Failed to fetch file: ${response.statusText}`);
            }
            
            const content = await response.text();
            
            this.currentFile = {
                path: filePath,
                content: content,
                downloadUrl: downloadUrl
            };
            
            this.displayFileContent(filePath, content);
            this.updateBreadcrumb(filePath);
            
            // Show download button
            document.getElementById('downloadBtn').style.display = 'block';
            
        } catch (error) {
            this.showError(`Failed to load file: ${error.message}`);
        } finally {
            this.showLoading(false);
        }
    }

    displayFileContent(filePath, content) {
        if (!this.monacoEditor) {
            console.error('Monaco editor not initialized');
            return;
        }
        
        const language = this.detectLanguage(filePath);
        const editorContainer = document.querySelector('.editor-container');
        
        // Show editor, hide placeholder
        editorContainer.classList.add('has-content');
        
        // Set editor content and language
        this.monacoEditor.setValue(content);
        monaco.editor.setModelLanguage(this.monacoEditor.getModel(), language);
    }

    detectLanguage(filePath) {
        const extension = filePath.split('.').pop()?.toLowerCase();
        
        const languageMap = {
            'js': 'javascript',
            'jsx': 'javascript',
            'ts': 'typescript',
            'tsx': 'typescript',
            'py': 'python',
            'java': 'java',
            'c': 'c',
            'cpp': 'cpp',
            'cc': 'cpp',
            'cxx': 'cpp',
            'h': 'c',
            'hpp': 'cpp',
            'cs': 'csharp',
            'html': 'html',
            'htm': 'html',
            'css': 'css',
            'scss': 'scss',
            'less': 'less',
            'json': 'json',
            'xml': 'xml',
            'yaml': 'yaml',
            'yml': 'yaml',
            'md': 'markdown',
            'markdown': 'markdown',
            'sql': 'sql',
            'sh': 'shell',
            'bash': 'shell',
            'zsh': 'shell',
            'ps1': 'powershell',
            'php': 'php',
            'rb': 'ruby',
            'go': 'go',
            'rs': 'rust',
            'swift': 'swift',
            'kt': 'kotlin',
            'scala': 'scala',
            'r': 'r'
        };
        
        return languageMap[extension] || 'plaintext';
    }

    updateBreadcrumb(filePath) {
        const breadcrumb = document.getElementById('breadcrumb');
        const pathParts = filePath.split('/');
        
        breadcrumb.innerHTML = pathParts.map(part => 
            `<span class="breadcrumb-item">${part}</span>`
        ).join('');
    }

    searchFiles(query) {
        const fileItems = document.querySelectorAll('.file-item');
        
        if (!query.trim()) {
            // Show all files
            fileItems.forEach(item => {
                item.style.display = 'flex';
            });
            // Show all children containers
            document.querySelectorAll('.file-children').forEach(children => {
                children.style.display = 'block';
            });
            return;
        }
        
        const searchTerm = query.toLowerCase();
        let hasVisibleItems = false;
        
        fileItems.forEach(item => {
            const fileName = item.querySelector('.file-name').textContent.toLowerCase();
            const filePath = item.dataset.path.toLowerCase();
            
            if (fileName.includes(searchTerm) || filePath.includes(searchTerm)) {
                item.style.display = 'flex';
                hasVisibleItems = true;
                // Show parent directories
                this.showParentDirectories(item);
            } else {
                item.style.display = 'none';
            }
        });
        
        // Handle empty search results
        const fileTreeContainer = document.getElementById('fileTree');
        if (!hasVisibleItems) {
            const existingMessage = fileTreeContainer.querySelector('.search-no-results');
            if (!existingMessage) {
                const noResultsDiv = document.createElement('div');
                noResultsDiv.className = 'search-no-results empty-state';
                noResultsDiv.innerHTML = '<p>No files found matching your search</p>';
                fileTreeContainer.appendChild(noResultsDiv);
            }
        } else {
            const existingMessage = fileTreeContainer.querySelector('.search-no-results');
            if (existingMessage) {
                existingMessage.remove();
            }
        }
    }

    showParentDirectories(fileItem) {
        let parent = fileItem.parentElement;
        while (parent && parent.classList.contains('file-children')) {
            parent.style.display = 'block';
            const parentPath = parent.dataset.parent;
            const parentItem = document.querySelector(`[data-path="${parentPath}"]`);
            if (parentItem) {
                const arrow = parentItem.querySelector('.expand-arrow');
                if (arrow) arrow.classList.add('expanded');
                parentItem.style.display = 'flex';
            }
            parent = parent.parentElement;
        }
    }

    changeEditorTheme(theme) {
        if (this.monacoEditor) {
            monaco.editor.setTheme(theme);
        }
    }

    downloadCurrentFile() {
        if (!this.currentFile) return;
        
        const blob = new Blob([this.currentFile.content], { type: 'text/plain' });
        const url = URL.createObjectURL(blob);
        const a = document.createElement('a');
        a.href = url;
        a.download = this.currentFile.path.split('/').pop();
        document.body.appendChild(a);
        a.click();
        document.body.removeChild(a);
        URL.revokeObjectURL(url);
    }

    getFileIcon(item) {
        if (item.type === 'dir') {
            return this.fileIcons.folder;
        }
        
        const extension = item.name.split('.').pop()?.toLowerCase();
        return this.fileIcons[extension] || this.fileIcons.file;
    }

    formatFileSize(bytes) {
        if (bytes === 0) return '0 B';
        const k = 1024;
        const sizes = ['B', 'KB', 'MB', 'GB'];
        const i = Math.floor(Math.log(bytes) / Math.log(k));
        return parseFloat((bytes / Math.pow(k, i)).toFixed(1)) + ' ' + sizes[i];
    }

    showLoading(show) {
        const overlay = document.getElementById('loadingOverlay');
        overlay.style.display = show ? 'flex' : 'none';
    }

    showError(message) {
        document.getElementById('errorMessage').textContent = message;
        document.getElementById('errorModal').style.display = 'flex';
    }
}

// Error modal functions
function closeErrorModal() {
    document.getElementById('errorModal').style.display = 'none';
}

// Initialize the application
document.addEventListener('DOMContentLoaded', () => {
    document.getElementById('repoUrl').value = "https://github.com/1820ANKIT2029/codeforces";
    new GitHubBrowser();
});

// Close modal when clicking outside
document.addEventListener('click', (e) => {
    const modal = document.getElementById('errorModal');
    if (e.target === modal) {
        closeErrorModal();
    }
});

// Keyboard shortcuts
document.addEventListener('keydown', (e) => {
    // Escape key closes modal
    if (e.key === 'Escape') {
        closeErrorModal();
    }
    
    // Ctrl/Cmd + F focuses search
    if ((e.ctrlKey || e.metaKey) && e.key === 'f') {
        e.preventDefault();
        document.getElementById('fileSearch').focus();
    }
});