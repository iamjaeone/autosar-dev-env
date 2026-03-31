pipeline {
    agent any

    stages {
        stage('1. Checkout') {
            steps {
                githubNotify status: 'PENDING', description: 'MISRA Check is running...'
                checkout scm
            }
        }

        stage('2. MISRA C Check (Cppcheck)') {
            steps {
                script {
                    sh 'cppcheck --enable=all --inconclusive --xml Static_Code/Reference_Code/ASW/ 2> cppcheck-result.xml'
                }
            }
        }

        stage('3. Publish Results') {
            steps {
                archiveArtifacts artifacts: 'cppcheck-result.xml', allowEmptyArchive: true
            }
        }
    }

    post {
        success {
            githubNotify status: 'SUCCESS', description: 'MISRA Check Passed!'
        }
        failure {
            githubNotify status: 'FAILURE', description: 'MISRA Check Failed. Please check the report.'
        }
    }
}