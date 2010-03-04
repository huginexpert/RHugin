\name{learn.cpt}
\alias{learn.cpt}

\title{Learn Conditional Probability Tables (CPTs)}

\description{
Use the EM algorithm to learn the conditional probability table for each node in the domain that has an experience table.
}

\usage{
learn.cpt(domain, tol = 1e-04, maxit = 0)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{tol}{a positive numeric value giving the stopping condition for the EM algorithm. The EM iterations stop when the relative difference in the log-likelihood between two successive iterations is smaller than \code{tol}.}
  \item{maxit}{a positive integer value giving the maximum number of EM iterations allowed or 0. The value 0 is interpreted as no limit on the number of EM iterations.}
}

\details{
Learning via EM algorithm requires that a non-empty set of cases be loaded into the domain.  Additionally, the learning algorithm will need to do inference so the domain must be compiled.  Since inference is performed multiple times, compiling the domain with \code{save = TRUE} often improves performance.
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_domain_learn_tables}, \code{h_domain_set_log_likelihood_tolerance} and \code{h_domain_set_max_number_of_em_iterations}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
For adding cases: \code{\link{set.cases}}, and for adding experience tables: \code{\link{get.table}}.
}

\examples{
# Create a Hugin domain
asia <- hugin.domain()

# Add nodes
nodes <- c("Asia", "Smoking", "Tuberculosis", "LungCancer",
            "Bronchitis", "Either", "XRay", "Dyspnoea")
for(node in nodes)
  add.node(asia, node, states = c("yes", "no"))

# Add edges
add.edge(asia, "Tuberculosis", "Asia")
add.edge(asia, "LungCancer", "Smoking")
add.edge(asia, "Bronchitis", "Smoking")
add.edge(asia, "Either", c("Tuberculosis", "LungCancer"))
add.edge(asia, "XRay", "Either")
add.edge(asia, "Dyspnoea", c("Either", "Bronchitis"))

# Add CPT for Either
cpt <- get.table(asia, "Either")
cpt$Freq <- c(1, 0, 1, 0, 1, 0, 0, 1)
set.table(asia, "Either", cpt)

# Add an experience table to every node except Either
nodes <- get.nodes(asia)
nodes <- nodes[-6]

for(node in nodes)
  tmp <- get.table(asia, node, type = "exp")

# Set cases
data(asia)
set.cases(asia, asia.cases)

# The domain must be compiled
compile(asia, save = TRUE)

# Learn Conditional Probability tables
learn.cpt(asia)
}

\keyword{programming}


