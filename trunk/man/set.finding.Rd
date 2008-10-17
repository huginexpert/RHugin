\name{set.finding}
\alias{set.finding}

\title{Set Finding}

\description{
Enter findings into a compiled RHugin domain object.
}

\usage{
set.finding(domain, node, finding, case = NULL)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{node}{a character string specifying the name of a node.}
  \item{finding}{a numeric vector containing the finding.  The length of \code{finding} must be equal to the number of states in \code{node} and all values must be nonnegative. Alternatively, \code{finding} may contain the name of a single state in \code{node}. In this case, the likelihood of that state is set to 1 and the likelihood for all other states is set to 0.}
  \item{case}{an integer between 1 and the number of cases in the domain.  When present, all existing evidence in the domain is retracted then the evidence in case \code{case} is entered.  Further, when \code{case} is provided the values of \code{node} and \code{finding} are ignored (and do not need to be provided).}
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/API_Manuals/}: \code{h_node_select_state}, \code{h_node_enter_finding} and \code{h_domain_enter_case}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{set.cases}}.
}

\examples{
demo("buildAppleTreeNetwork")

# Compile the domain
compile(AppleTree)

# Set finding
set.finding(AppleTree, "Loses", c(1, 0))

# Or equivalently
set.finding(AppleTree, "Loses", "yes")
}

\keyword{programming}


